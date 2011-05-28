#ifndef ESTADO_GAMEOVER_H
#define ESTADO_GAMEOVER_H

#include "EstadoJuego.h"
#include "GUIAux.h"

class EstadoGameOver : public EstadoJuego
{
    public:
        EstadoGameOver();
        ~EstadoGameOver();

        void entrar();
        void actualizar();
        void pintar();
        void salir();

        void buttonDown(Gosu::Button btn);
        void buttonUp(Gosu::Button btn);

        void leerInput();

        void ejecutarBeat(int tipo);

    private:
        // Fondo del menú
        boost::scoped_ptr<Gosu::Image> fondo;
};

#endif