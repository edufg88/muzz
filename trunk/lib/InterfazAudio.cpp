#include "InterfazAudio.h"
#include "DatosCancion.h"
#include "ProcesadorAudio.h"
#include "Juego.h"

InterfazAudio* InterfazAudio::instancia = NULL;

InterfazAudio* InterfazAudio::getInstancia()
{
    if (instancia == NULL)
    {
        instancia = new InterfazAudio();
    }

    return instancia;
}

InterfazAudio::InterfazAudio()
{
    cout << "CREO INTERFAZ AUDIO NUEVA" << endl;
    numeroDeBeats = new int[3];
    for (int i = 0; i < 3; i++)
        numeroDeBeats[i] = 0;

    mediaDeBeats = new int[3];
    for (int i = 0; i < 3; i++)
        mediaDeBeats[i] = 0;
}

InterfazAudio::~InterfazAudio()
{
    instancia = NULL;

    cout << "BORRANDO INTERFAZ AUDIO" << endl;
    // Cerramos todo el sistema de sonido
    inputChannel->setPaused(true);
    inputChannel->stop();
    result = sound->release();
    ERRCHECK(result);
    result = inputChannelGroup->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    if (datosCancion != NULL)
    {
        delete datosCancion;
    }
    datosCancion = NULL;

    if (numeroDeBeats != NULL)
    {
        delete numeroDeBeats;
    }
    numeroDeBeats = NULL;

    if (mediaDeBeats != NULL)
    {
        delete mediaDeBeats;
    }
    mediaDeBeats = NULL;
}

bool InterfazAudio::inicializarAudio()
{
    bool res = true;
    // Creamos un nuevo almacén para los datos de la canción
    datosCancion = new DatosCancion();
    // Creamos Sistema FMOD
    result = FMOD::System_Create(&system);
    res = ERRCHECK(result);
    // Inicializamos FMOD
    result = system->init(100, FMOD_INIT_NORMAL, 0);
    res = ERRCHECK(result);
    // Inicializamos el grupo de canales
    result = system->createChannelGroup("ICG1", &inputChannelGroup);
    res = ERRCHECK(result);
    // Hay que cargar siempre una canción
    cargarCancion("media/aux.mp3");
    return res;
}

void InterfazAudio::actualizar()
{
    // Controlamos la pausa
    if(segundosPausa > 0)
    {
        if ((Gosu::milliseconds() - contadorPausa) > segundosPausa*1000)
        {
            setPaused(false);
            segundosPausa = 0;
        }
    }

    // Actualizamos el sistema
    result = system->update();

    ERRCHECK(result);

    // Aux
//    cout << "Beat(BASS): " << numeroDeBeats[0] << endl;
//    cout << "Beat(MID): " << numeroDeBeats[1] << endl;
//    cout << "Beat(HIGH): " << numeroDeBeats[2] << endl;


//    float vector[16];
//    inputChannel->getWaveData(vector, 16, 0);
//
//    for (int i = 0; i < 16; i++)
//    {
//        cout << vector[i] << endl;
//    }
//    cout << "-----------------------------" << endl << endl;
}

void InterfazAudio::obtenerDatos()
{
    datosCancion->obtenerDatos();
}

bool InterfazAudio::cargarCancion(const char* ruta)
{
    result = system->createStream(ruta, FMOD_2D | FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sound);
    return (ERRCHECK(result));
}

bool InterfazAudio::playCancion()
{
    bool res = true;
    result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &inputChannel);
    res = ERRCHECK(result);
    result = inputChannel->setChannelGroup(inputChannelGroup);
    res = ERRCHECK(result);
    result = inputChannel->setPaused(false);
    res = ERRCHECK(result);
    datosCancion->setVolumen(0.5);
    datosCancion->setPan(0);

    return res;
}

bool InterfazAudio::stopCancion()
{
    bool res = true;
    setPosicion(0);
    result = inputChannel->stop();
    res = ERRCHECK(result);
    return res;
}

void InterfazAudio::setPosicion(int ms)
{
    inputChannel->setPosition(ms, FMOD_TIMEUNIT_MS);
}

void InterfazAudio::pausar(int segs)
{
    contadorPausa = Gosu::milliseconds();
    segundosPausa = segs;
    setPaused(true);
}

void InterfazAudio::setPaused(bool p)
{
    result = inputChannel->setPaused(p);
}

bool InterfazAudio::cargarEfecto(const char* ruta, string nombre)
{
    FMOD::Sound* efecto;
    result = system->createSound(ruta, FMOD_2D | FMOD_SOFTWARE | FMOD_LOOP_OFF, 0, &efecto);
    // Almacenamos el efecto para acceder a el cuando sea necesario
    efectos[nombre] = efecto;

    return (ERRCHECK(result));
}
        
bool InterfazAudio::playEfecto(string nombre)
{
    result = system->playSound(FMOD_CHANNEL_FREE, efectos[nombre], false, &inputChannel);
    return (ERRCHECK(result));
}

bool InterfazAudio::ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << endl;
        return false;
    }

    return true;
}

DatosCancion* InterfazAudio::getDatosCancion() const
{
    return datosCancion;
}

FMOD::System* InterfazAudio::getSystem() const
{
    return system;
}

FMOD::ChannelGroup* InterfazAudio::getChannelGroup() const
{
    return inputChannelGroup;
}

FMOD::Channel* InterfazAudio::getChannel() const
{
    return inputChannel;
}

FMOD::Sound* InterfazAudio::getSound() const
{
    return sound;
}

int InterfazAudio::getNumeroDeBeats(int tipo) const
{
    switch (tipo)
    {
        case BASSBEAT:
            return numeroDeBeats[0];
        case MIDBEAT:
            return numeroDeBeats[1];
        case HIGHBEAT:
            return numeroDeBeats[2];
        default:
            cerr << "Error en getNumeroDeBeats, tipo desconocido" << endl;
            return -1;
    }
}

void InterfazAudio::setNumeroDeBeats(int* beats)
{
    for (int i = 0; i < 3; i++)
    {
        numeroDeBeats[i] = beats[i];
    }
}

int InterfazAudio::getMediaBeats(int tipo) const
{
    switch (tipo)
    {
        case BASSBEAT:
            return mediaDeBeats[0];
        case MIDBEAT:
            return mediaDeBeats[1];
        case HIGHBEAT:
            return mediaDeBeats[2];
        default:
            cerr << "Error en getMediaBeats, tipo desconocido" << endl;
            return -1;
    }
}

void InterfazAudio::setMediaBeats(int* beats)
{
    mediaDeBeats[0] = beats[0];
    mediaDeBeats[1] = beats[1];
    mediaDeBeats[2] = beats[2];
}