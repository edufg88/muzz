#include "Camara.h"
#include "Juego.h"

Camara::Camara(int x, int y)
{
    setPos(x, y);
    setLimites(5000, 5000);
}

Camara::~Camara()
{

}

bool Camara::enlazarCamara(Objeto* o)
{
    if (o == NULL)
    {
        return false;
    }
    else
    {
        objeto = o;
        return true;
    }
}

void Camara::actualizar()
{      
    // La Y la podemos cambiar si queremos cierto scroll vertical
    setPos(objeto->getX() - Juego::getInstancia()->graphics().width() / 2, 0);
}

void Camara::setPos(int x, int y)
{
    Juego* j = Juego::getInstancia();
    posX = x;
    posY = y;
    if (posX < 0) posX = 0;
    if (posY < 0) posY = 0;
    /*
    
    if (posX > limiteX - j->graphics().width())
        posX = limiteX - j->graphics().width();
    if (posY > limiteY - j->graphics().height())
        posY = limiteY - j->graphics().height();
     */
}

void Camara::setLimites(int x, int y)
{
    limiteX = x;
    limiteY = y;
}

int Camara::getX() const
{
    return posX;
}

int Camara::getY() const
{
    return posY;

}