#ifndef ESTADO_FIN_H
#define ESTADO_FIN_H

#include "EstadoJuego.h"
#include "GUIAux.h"

class EstadoFin : public EstadoJuego
{
    public:
        EstadoFin();
        ~EstadoFin();

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