#include "GUI/Panel.h"
#include "Juego.h"

Panel::Panel(int x, int y) : ElementoGUI(x, y)
{
    animacion = NULL;
}

Panel::Panel(Animacion* pAnimacion, int x, int y) : ElementoGUI(x, y)
{
    setAnimacion(pAnimacion);
}

Panel::~Panel()
{
    if (animacion != NULL)
    {
        delete animacion;
    }
    animacion = NULL;
}

void Panel::setAnimacion (Animacion* pAnimacion)
{
    animacion = pAnimacion;
}

Animacion* Panel::getAnimacion () const
{
    return animacion;
}

void Panel::actualizar()
{

}

void Panel::pintar()
{
    if (visible)
        animacion->getImagenActual()->draw(posX, posY, ZGUI);
}

float Panel::ancho() const
{
    return animacion->getImagen(0)->width();
}

float Panel::alto() const
{
    return animacion->getImagen(0)->height();
}