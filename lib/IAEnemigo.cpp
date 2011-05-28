#include "IAEnemigo.h"

IAEnemigo::IAEnemigo()
{
    actitud = PASIVO;
}

IAEnemigo::IAEnemigo(int pActitud)
{
    actitud = pActitud;
}

IAEnemigo::~IAEnemigo()
{

}

int IAEnemigo::getActitud() const
{
    return actitud;
}

void IAEnemigo::setActitud(int act)
{
    actitud = act;
}