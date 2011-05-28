#ifndef JUEGO_H
#define JUEGO_H

#include "GosuAux.h"

#include <iostream>
#include "EstadoJuego.h"
#include "ProcesadorAudio.h"
#include "InterfazFisica.h"
#include "InterfazIA.h"
#include "Protagonista.h"
#include "GUI/Panel.h"
using namespace std;

// Estados del juego
#define ESTADO_MENU 1
#define ESTADO_CANCION 2
#define ESTADO_PARTIDA 3
#define ESTADO_GAMEOVER 4
#define ESTADO_FIN 5
#define ESTADO_TUTORIAL 6

/**
 * JUEGO, singleton para facilitar el acceso al sistema GOSU
 */
class Juego : public Gosu::Window
{
    public:
        static Juego* getInstancia();
        ~Juego();
        bool cambiarEstado(int estado);
        void inicializar();
        void update();
        void draw();

        void buttonDown(Gosu::Button btn);
        void buttonUp(Gosu::Button btn);

        void ejecutarBeat(int tipo);
        void analizarCancion();

        Protagonista* getProtagonista() const;

        bool getJugando () const;
        void setJugando(bool jugando);
        void setFinalizado();

        void limpiar();
        void reiniciar();
        void salir();

        // Marca de tiempo del ultimo beat;
        long ultimoBeat;

    private:
        Juego();
        static Juego* instancia;
        EstadoJuego* estado;
        InterfazAudio* audio;
        InterfazFisica* fisica;
        InterfazIA* ia;
        ProcesadorAudio* procesadorAudio;
        // Indica si nos encontramos en una partida o no
        bool jugando;
        bool pausado;
        Panel* panelPausa;
        

};

#endif