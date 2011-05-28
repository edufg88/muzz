#include "GUI/Boton.h"
#include "Juego.h"
#include "Animacion.h"

Boton::Boton(int x, int y) : ElementoGUI(x, y)
{
    animacion = NULL;
}

Boton::Boton(Animacion* pAnimacion, int x, int y) : ElementoGUI(x, y)
{
    setAnimacion(pAnimacion);
}

Boton::~Boton()
{
    if (animacion != NULL)
    {
        delete animacion;
    }
    animacion = NULL;
}

void Boton::setAnimacion (Animacion* pAnimacion)
{
    animacion = pAnimacion;
}

Animacion* Boton::getAnimacion () const
{
    return animacion;
}

void Boton::actualizar()
{

}

void Boton::pintar()
{
    if (visible)
    {
        if (mouseOver())
        {
            animacion->getImagen()->draw(posX, posY, ZGUI, 1.05f, 1.05f);
        }
        else
            animacion->getImagen()->draw(posX, posY, ZGUI);
    }
}

bool Boton::mouseOver() const
{
    bool mo = false;

    double xRaton = Juego::getInstancia()->input().mouseX();
    double yRaton = Juego::getInstancia()->input().mouseY();

    if ((xRaton >= posX) && (xRaton <= posX + animacion->getImagenActual()->width()))
    {
        if ((yRaton >= posY) && (yRaton <= posY + animacion->getImagenActual()->height()))
        {
            mo = true;
        }
    }

    return mo;
}