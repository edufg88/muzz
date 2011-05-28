#include <iostream>
#include <math.h>
#include "ProcesadorAudio.h"
#include "Juego.h"
#include "DatosCancion.h"
using namespace std;

ProcesadorAudio::ProcesadorAudio()
{
    timeCounter = Gosu::milliseconds();
    numberOfBeats = new int[3];
    countingBeats = new int[3];
    meanValues = new int[3];

    for (int i = 0; i < 3; i++)
    {
        numberOfBeats[i] = 0;
        countingBeats[i] = 0;
        meanValues[i] = 0;
    }
    
    audio = InterfazAudio::getInstancia();

    bbUpCounter = 0;
    bbMidUpCounter = 0;
    bbHighUpCounter = 0;

    bassCutoff = 6;//6
    midCutoff = 16;
    highCutoff = 32;

    historySize = 43; // Debería ser 43 en vez de 20?
    decibelCutoff = 0; // Por determinar

    bassThreshold = 145.0f;
    midThreshold = 130.0f; 
    highThreshold = 100.0f;

    // FFT
    eFFTBuffer.resize(spectrumSize, 0.0f); // Establecemos el tamaño del espectro a 1024
    fftwIn = (fftw_complex*) fftw_malloc(sizeof (fftw_complex) * spectrumSize);
    fftwOut = (fftw_complex*) fftw_malloc(sizeof (fftw_complex) * spectrumSize);
    fftwP = fftw_plan_dft_1d(1024, fftwIn, fftwOut, FFTW_FORWARD, FFTW_ESTIMATE);

    // Inicializamos si el sistema se ha iniciado correctamente
    eHistory.resize(subbands); // Establecemos en 64 el número de subbandas
    for (int i = 0; i < subbands; i++)
    {
        eHistory[i].resize(historySize);
    }

    // Inicializamos los datos del espectro
    spectrumBuffer = new float[spectrumSize];
    eMean.resize(subbands, 0.0f);
    eSubband.resize(subbands, 0.0f);
    eVariance.resize(subbands);
    dbSpectrumBuffer.resize(spectrumSize/2, 0.0f);

}

ProcesadorAudio::~ProcesadorAudio()
{
    if (numberOfBeats != NULL)
        delete numberOfBeats;
    numberOfBeats = NULL;

    if (countingBeats != NULL)
        delete countingBeats;
    countingBeats = NULL;

    if (meanValues != NULL)
    {
        delete meanValues;
    }
    meanValues = NULL;


    if (spectrumBuffer != NULL)
    {
        delete spectrumBuffer;
    }
    spectrumBuffer = NULL;

        
    fftw_destroy_plan(fftwP);
    fftw_free(fftwIn);
    fftw_free(fftwOut);
}

void ProcesadorAudio::update()
{
    // Actualizamos el sistema
    // system->update();

    // Actualizamos el espectro en el sistema
    audio->getChannelGroup()->getSpectrum(this->spectrumBuffer, spectrumSize, 0, FMOD_DSP_FFT_WINDOW_RECT);

    float max = 0.0f;
    for (int i = 0; i < spectrumSize; i++)
    {
        if (spectrumBuffer[i] > max) 
        {
            max = spectrumBuffer[i];
        }
    }
    // Calculamos los decibelios
    if (max > 0.001f)
    {
        for (int i = 0; i < spectrumSize/2; i++)
        {
            float val, db;
            val = spectrumBuffer[i+1];

            db = 10.0f * static_cast<float>(log10(val)) * 2.0f;
            val = db;

            //if (val < -decibelCutoff)
               // val = -decibelCutoff;

            //val = val / -static_cast<float>(decibelCutoff);

            val = 1.0f - val;
            dbSpectrumBuffer[i] = val;
        }
    }

    // Controlamos si los beats cada 5 segundos
    controleBeats();

}

void ProcesadorAudio::controleBeats()
{
    // Cada 5 segundos, comprobamos la cuenta de beats
    if ((Gosu::milliseconds() - timeCounter) >= 1000)
    {
        // Actualizamos el reloj
        timeCounter = Gosu::milliseconds();

        for (int i = 0; i < 3; i++)
        {
            // Pasamos la copia actual a la copia válida
            numberOfBeats[i] = countingBeats[i];
            // Reiniciamos el contador para los próximos 5 segundos
            countingBeats[i] = 0;
        }

        //cout << "BASS: " << numberOfBeats[0] << " MID: " << numberOfBeats[1] << " HIGH: " << numberOfBeats[2] << endl;
        audio->setNumeroDeBeats(numberOfBeats);
    }

    //cout << countingBeats[0] << ", " << countingBeats[1] << ", " << countingBeats[2] << endl;
}

void ProcesadorAudio::process()
{
    // Reseteamos los contadores
    if (bbUpCounter > 0)
        bbUpCounter--;

    if (bbMidUpCounter > 0)
        bbMidUpCounter--;

    if (bbHighUpCounter > 0)
        bbHighUpCounter--;

    // Cogemos los valores para FFT (las 1024 amplitudes)
    for (int i = 0; i < spectrumSize; i++)
    {
        fftwIn[i][0] = spectrumBuffer[i];
        fftwIn[i][1] = 0.0f; // Aquí podríamos meter el buffer izquierdo
    }

    // Realizamos FFT
    fftw_execute(fftwP);

    // Calculamos las 1024 amplitudes de frecuencia de nuestra señal
    // eFFTBuffer = B 
    for (int i = 0; i < spectrumSize; i++)
    {
        eFFTBuffer[i] = sqrt(pow(fftwOut[i][0], 2) + pow(fftwOut[i][1], 2));
    }

    // Calculamos la energía
    // eSubband = Es 
    int j = 0;
    for (int i = 0; i < spectrumSize; i++)
    {
        j = i / (spectrumSize / subbands);
        eSubband[j] += eFFTBuffer[i] * 10.0f; // Normalizado...probar sin multiplicar
    }

    // Añadimos la energía al histórico
    // eHistory = Ei
    for (int i = 0; i < subbands; i++)
    {
        eSubband[i] = eSubband[i] / (spectrumSize / subbands);
        eHistory[i].push_back(eSubband[i]);
    }

    // Corremos una posición el histórico y recalculamos la media
    // eMean = <Ei> (en tutorial)
    for (int i = 0; i < subbands; i++)
    {
        eMean[i] = 0.0f;

        while (eHistory[i].size() > static_cast<unsigned int>(historySize))
        {
            eHistory[i].erase(eHistory[i].begin());
        }
        for (int j = 0; j < static_cast<int>(historySize); j++)
        {
            eMean[i] += eHistory[i][j];
        }
        eMean[i] = eMean[i] / historySize;
    }

    // Calculamos la varianza (o desviación estándar)
    for (int i = 0; i < subbands; i++)
    {
        eVariance[i] = 0.0f;
        for (unsigned int j = 0; j < eHistory[i].size(); j++)
        {
            // Umbral de 145 funciona mejor con la varianza y 157 con la desviación estándar
            eVariance[i] += fabs(eHistory[i][j] - eMean[i]);
        }
        eVariance[i] = eVariance[i] / historySize;
    }

    // Algunas variables para el análisis
    unsigned short bassCount = 0;
    unsigned short midCount = 0;
    unsigned short highCount = 0;

    float lowMean = 0.0f;
    float lowPeak = 0.0f;
    float midMean = 0.0f;
    float midPeak = 0.0f;
    float highMean = 0.0f;
    float highPeak = 0.0f;

    // Comprobamos cada pico de energía respecto al umbral y los valores medios.
    // Si está por encima de la media*umbral*C entonces detectamos un beat
    // en ese subespectro.
    for (int i = 0; i < subbands; i++)
    {
        if (i < bassCutoff)
        {
            lowMean += eMean[i];
            lowPeak += eSubband[i];

            if (eSubband[i] > (eVariance[i]/eMean[i]) + (eMean[i]*(bassThreshold/100.0)))
            {
                bassCount++;
            }
        }
        else if (i < midCutoff)
        {
            midMean += eMean[i];
            midPeak += eSubband[i];

            if (eSubband[i] > (eVariance[i]/eMean[i]) + (eMean[i]*(midThreshold/100.0)))
            {
                midCount++;
            }
        }
        else if (i < highCutoff)
        {
            highMean += eMean[i];
            highPeak += eSubband[i];

            if (eSubband[i] > (eVariance[i]/eMean[i]) + (eMean[i]*(highThreshold/100.0)))
            {
                highCount++;
            }
        }
    }

    // Comprobamos los contadores de picos en el super-sub espectro.
    // Si hay suficientes, entonces hemos encontrado beat
    if (bbUpCounter == 0)
    {
        if (bassCount > bassCutoff/2)
        {
            bbUpCounter = 1;
            bassBeatEnergy = lowPeak;

            // Lanzamos el evento en el juego
            Juego::getInstancia()->ejecutarBeat(BASSBEAT);
            // Sumamos 1 al contador de beats (BASS BEAT)
            countingBeats[0]++;

            //cout << "BASS" << endl;
        }
        else
        {
            Juego::getInstancia()->ejecutarBeat(NOBEAT);
        }
    }
    if (bbMidUpCounter == 0)
    {
        if (midCount > (midCutoff-bassCutoff)/2)
        {
            bbMidUpCounter = 1;
            midBeatEnergy = midPeak;
            // Lanzamos el evento en el juego
            Juego::getInstancia()->ejecutarBeat(MIDBEAT);
            // Sumamos 1 al contador de beats (MID BEAT)
            countingBeats[1]++;

            //cout << "MID" << endl;
        }
        else
        {
            //Juego::getInstancia()->ejecutarBeat(NOBEAT);
        }
    }
    if (bbHighUpCounter == 0)
    {
        if (highCount > (highCutoff - midCutoff)/2)
        {
            bbHighUpCounter = 1;
            highBeatEnergy = highPeak;
            // Lanzamos el evento en el juego
            Juego::getInstancia()->ejecutarBeat(HIGHBEAT);
            // Sumamos 1 al contador de beats (HIGH BEAT)
            countingBeats[2]++;
            //cout << "HIGH" << endl;
        }
        else
        {
            //Juego::getInstancia()->ejecutarBeat(NOBEAT);
        }
    }
}

void ProcesadorAudio::firstAnalysis()
{
    int analysis = 0;
    int init[3];
    int beats[3][3]; // Aquí almacenamos la cuenta de 3 tipos de beats en cada uno de los 3 tramos
    int resBeats[3];
    int mainBeat; // 3 = BASS, 2 = MID; 1 = HIGH
    int duracion = audio->getDatosCancion()->getDuracion();

    // Inicializamos
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            beats[i][j] = 0;
    
    // Marcamos donde empieza cada tramo que vamos a analizar
    init[0] = duracion / 3 / 2;
    init[1] = init[0] + duracion/3;
    init[2] = init[1] + duracion/3;

    bool end = false;

    
    audio->playCancion();
    audio->setPosicion(init[analysis]);
    
    loadTimeCounter = Gosu::milliseconds();
    
    long refreshCounter = Gosu::milliseconds();
    long sumCounter = Gosu::milliseconds();

    while (!end)
    {
        if ((Gosu::milliseconds() - refreshCounter) > 16)
        {
            audio->actualizar();
            update();
            process();
            refreshCounter = Gosu::milliseconds();
        }

        // El análisis general se hace cada segundo
        if ((Gosu::milliseconds() - sumCounter) > 1000)
        {
            beats[analysis][0] += numberOfBeats[0];
            beats[analysis][1] += numberOfBeats[1];
            beats[analysis][2] += numberOfBeats[2];
            sumCounter = Gosu::milliseconds();
        }

        // Hacemos análisis de 3 tramos de 5 segundos
        if ((Gosu::milliseconds() - loadTimeCounter) > 5000)
        {
            cout << "ANALISIS PREVIO ( " << analysis << " )" << endl;
            cout << beats[analysis][0] << ", " << beats[analysis][1]  << ", " << beats[analysis][2] << endl;

            // Avanzamos al siguiente análisis
            if (analysis < 3)
            {
                analysis++;
                audio->setPosicion(init[analysis]);
            }

            loadTimeCounter = Gosu::milliseconds();
        }

        if (analysis == 3)
            end = true;
    }

    audio->stopCancion();

    // Analizamos los datos obtenidos //
    ///////////////////////////////////

    // Calculamos la media de los valores
    resBeats[0] = (beats[0][0] + beats[1][0] + beats[2][0])/3.0;
    resBeats[1] = (beats[0][1] + beats[1][1] + beats[2][1])/3.0;
    resBeats[2] = (beats[0][2] + beats[1][2] + beats[2][2])/3.0;

    meanValues[0] = resBeats[0] / 5;
    meanValues[1] = resBeats[1] / 5;
    meanValues[2] = resBeats[2] / 5;

    audio->setMediaBeats(meanValues);

    cout << "VALORES MEDIOS "<< endl;
    cout << meanValues[0] << ", " << meanValues[1]  << ", " << meanValues[2] << endl;
}