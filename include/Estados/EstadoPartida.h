#ifndef ESTADO_PARTIDA_H
#define ESTADO_PARTIDA_H

#include <list>
#include "DatosPartida.h"
#include "EstadoJuego.h"
#include "Protagonista.h"
#include "Camara.h"
#include "GUIAux.h"
#include "Nivel.h"
// Temporal
#include "Enemigos/Bola.h"
#include "Enemigos/Cuadrado.h"
#include "Enemigos/Gusano.h"
#include "Enemigos/Rueda.h"

using namespace std;

class EstadoPartida : public EstadoJuego
{
    public:
        EstadoPartida();
        ~EstadoPartida();

        void entrar();
        void actualizar();
        void pintar();
        void salir();

        void buttonDown(Gosu::Button btn);
        void buttonUp(Gosu::Button btn);
        void leerInput();
        void ejecutarBeat(int tipo);
        Protagonista* getProtagonista() const;
        void setFinalizado();

    private:
        DatosPartida* datosPartida;
        Camara* camara;
        Protagonista* personaje;
        void inicializarProtagonista();
        // Nivel de juego
        Nivel* nivel;
        // Cara del personaje que representa su estado
        Panel* panelCara;
        Panel* panelVida;
        Panel* panelEscudo;
        Texto* textoPuntos;
        Texto* puntuacion;
        Texto* textoVolumen;
        Texto* volumen;
        Texto* textoPan;
        Texto* pan;
        Texto* duracion;
        Texto* textoInicial;
        long timerTextoInicial;

        void inicializarGUI();
        void pintarGUI();
        void actualizarGUI();
};

#endif