#ifndef PROCESADOR_AUDIO_H
#define PROCESADOR_AUDIO_H

#include "InterfazAudio.h"
#include "FMODAux.h"
#include <vector>
using namespace std;

#define subbands 64
#define spectrumSize 1024

#define NOBEAT 0
#define HIGHBEAT 1
#define MIDBEAT 2
#define BASSBEAT 3

class ProcesadorAudio
{
    public:
        ProcesadorAudio();
        ~ProcesadorAudio();
        virtual void update();
        virtual void process();
        void firstAnalysis();

    private:
        // Enlace con FMOD
        InterfazAudio* audio;

        // Para el análisis del espectro, esto es el "poder" del beat
        float bassBeatEnergy;
        float midBeatEnergy;
        float highBeatEnergy;

        // Valor de corte para convertir el espectro en decibelios
        float decibelCutoff;

        // Valores para contar los procesos entre beats sucesivos,
        // los beats muy juntos se consideran como 1
        unsigned short bbUpCounter;
        unsigned short bbMidUpCounter;
        unsigned short bbHighUpCounter;

        // Band count (puede ser transformado a frecuencia)
        unsigned short bassCutoff;
        unsigned short midCutoff;
        unsigned short highCutoff;

        // Hasta cuanto almacenaremos de historia (1 segundo por norma)
        unsigned short historySize;

        // Constantes que se multiplican por la varianza de las energias medias
        // en cada una de las subbandas para determinar si un beat es suficientemente
        // fuerte para ser contado
        float bassThreshold;
        float midThreshold;
        float highThreshold;

        // Historico de energías sobre un periodo de tiempo para cada subbanda.
        vector< vector<float> > eHistory;

        // Datos del espectro ---
        float *spectrumBuffer;
        vector <float> dbSpectrumBuffer; // Almacena el espectro en decibelios

        // Subdivisiones ---
        // Energia instantanea de una subbanda en concreto
        vector <float> eSubband;
        // Media del historico para cada subbanda
        vector <float> eMean;
        // Varianza o desviación estandar
        vector <float> eVariance;

        // Para la FFT (Fast Fourier Transformation) ---
        // Almacena los datos de la transformada para cada subbanda
        vector<float> eFFTBuffer;
        // Almacenan los datos de la FFT
        fftw_complex *fftwIn, *fftwOut;
        // Plan de ejecución
        fftw_plan fftwP;

        // Contador de tiempo para los beats
        int timeCounter;
        // Contador de tiempo para el análisis previo
        int loadTimeCounter;
        /** Número de beats de los últimos 5 segundos (válido)
         * [0] -> bassBeats
         * [1] -> midBeats
         * [2] -> highBeats
         * */
        int* numberOfBeats;
        // Número de beats de los 5 segundos que se encuentra procesando actualmente (no válido)
        int* countingBeats;
        // Valores medios del análisis previo
        int* meanValues;
        
        void controleBeats();

};

#endif