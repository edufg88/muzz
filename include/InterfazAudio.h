#ifndef INTERFAZ_AUDIO_H
#define INTERFAZ_AUDIO_H

#include "FMODAux.h"
#include <iostream>
#include <map>
using namespace std;

class DatosCancion;

class InterfazAudio
{
    public:
        static InterfazAudio* getInstancia();
        void setNull() {instancia = NULL;}
        ~InterfazAudio();
        bool inicializarAudio();
        void actualizar();
        // Carga la canción principal del nivel (Sólo hay una)
        bool cargarCancion(const char* ruta);
        // Carga un efecto y lo añade a la lista de efectos
        bool cargarEfecto(const char* ruta, string nombre);
        // Reproduce la canción principal
        bool playCancion();
        // Detiene la canción principal
        bool stopCancion();
        // Pausa o continua la canción principal
        void setPaused(bool p);
        // Pausa la canción un determinado número de segundos
        void pausar(int segs);
        // Repruduce un efecto determinado
        bool playEfecto(string nombre);
        // Cambia segundo por el que se encuentra la reproduccion de la canción
        void setPosicion(int ms);
        // Obtiene los datos de la canción
        void obtenerDatos();
        // Obtiene el número de beats de la canción en los últimos 5 segundos
        int getNumeroDeBeats(int tipo) const;
        void setNumeroDeBeats(int* beats);
        // Obtiene el número de beats de referencia
        int getMediaBeats(int tipo) const;
        void setMediaBeats(int* beats);

        DatosCancion* getDatosCancion() const;
        FMOD::System* getSystem() const;
        FMOD::ChannelGroup* getChannelGroup() const;
        FMOD::Channel* getChannel() const;
        FMOD::Sound* getSound() const;

    private:
        InterfazAudio();
        static InterfazAudio* instancia;
        DatosCancion* datosCancion;
        FMOD::System* system;
        FMOD_RESULT result;
        FMOD::ChannelGroup *inputChannelGroup;
        FMOD::Channel *inputChannel;
        // Sonido para la canción principal
        FMOD::Sound* sound;
        // Sonidos para efectos
        map<string, FMOD::Sound*> efectos;
        /*Beats en los últimos 5 segundos
         * [0] -> bassBeats
         * [1] -> midBeats
         * [2] -> highBeats
         * */
        int* numeroDeBeats;
        // Valores de referencia extraídos del análisis previo
        int* mediaDeBeats;
        // Contador para las pausas
        int contadorPausa;
        // Valor de la pausa
        int segundosPausa;

        bool ERRCHECK(FMOD_RESULT result);
};

#endif