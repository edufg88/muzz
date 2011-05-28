#ifndef ESTADO_TUTORIAL_H
#define ESTADO_TUTORIAL_H

#include "EstadoJuego.h"
#include "GUIAux.h"

class EstadoTutorial : public EstadoJuego
{
    public:
        EstadoTutorial();
        ~EstadoTutorial();

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
         /**
         * Elementos GUI
         */
        Boton* bAnterior;
        Boton* bSiguiente;

        void inicializarGUI();
        void pintarGUI();

        void paginaSiguiente();
        void paginaAnterior();

        int pagina;
};

#endif