#ifndef ESTADO_MENU_H
#define ESTADO_MENU_H

#include "EstadoJuego.h"
#include "GUIAux.h"

class EstadoMenu : public EstadoJuego
{
    public:
        EstadoMenu();
        ~EstadoMenu();

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
        Boton* botonJugar;
        Boton* botonHTP;
        Boton* botonSalir;

        void inicializarGUI();
        void pintarGUI();


};

#endif
