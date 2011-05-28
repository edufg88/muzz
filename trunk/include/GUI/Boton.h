#ifndef BOTON_H
#define BOTON_H

#include "ElementoGUI.h"
#include "GosuAux.h"
#include "Animacion.h"
using namespace std;

class Boton : public ElementoGUI
{
    public:
        Boton(int x, int y);
        Boton(Animacion* pAnimacion, int x, int y);
        ~Boton();
        void setAnimacion(Animacion* pAnimacion);
        Animacion* getAnimacion() const;

        // Heredadas
        void actualizar();
        void pintar();

        bool mouseOver() const;

    private:
        Animacion* animacion;
};

#endif