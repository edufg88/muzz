#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H

#include "GosuAux.h"
#include "ElementoGUI.h"
#include <iostream>
using namespace std;

class Juego;

class EstadoJuego
{
    public:
        EstadoJuego();
        virtual ~EstadoJuego() = 0;
        virtual void entrar() = 0;
        virtual void actualizar() = 0;
        virtual void pintar() = 0;
        virtual void salir() = 0;


        /**
         * Estas funciones capturan eventos
         * @param btn
         */
        virtual void buttonDown(Gosu::Button btn);
        virtual void buttonUp(Gosu::Button btn);

        // Esta función lee el input (puede leer si sigue pulsado un botón)
        virtual void leerInput() = 0;

        // Esta función ejecuta una acción en función del beat recibido
        virtual void ejecutarBeat(int tipo) = 0;

    protected:

};

#endif