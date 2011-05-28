#ifndef PANEL_H
#define PANEL_H

#include "ElementoGUI.h"
#include "Animacion.h"
#include "GosuAux.h"
using namespace std;

class Panel : public ElementoGUI
{
    public:
        Panel(int x, int y);
        Panel(Animacion* pAnimacion, int x, int y);
        ~Panel();
        void setAnimacion(Animacion* pAnimacion);
        Animacion* getAnimacion() const;

        // Heredadas
        void actualizar();
        void pintar();

        float ancho() const;
        float alto() const;

    private:
        // Se utilizará una animación que puede ser una o varias imágenes
        Animacion* animacion;
};

#endif