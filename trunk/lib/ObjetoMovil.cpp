#include "ObjetoMovil.h"
#include "Juego.h"

ObjetoMovil::ObjetoMovil(string nombre, float32 x, float32 y) : Objeto(nombre, x, y)
{
    
}

ObjetoMovil::~ObjetoMovil()
{

}

void ObjetoMovil::pintar() const
{

}

void ObjetoMovil::actualizar()
{
    Objeto::actualizar();
}

void ObjetoMovil::setPos(float32 x, float32 y)
{
    posX = x;
    posY = y;
}