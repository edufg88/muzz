#include "IAEnemigos/IABola.h"
#include "Juego.h"

int IABola::rangoVision = 400;

IABola::IABola()
{
}

IABola::IABola(int actitud) : IAEnemigo(actitud)
{

}

IABola::~IABola()
{

}

void IABola::actualizar()
{
    actualizarPosProta();
}

void IABola::actualizarPosProta()
{
    Protagonista* p = Juego::getInstancia()->getProtagonista();
    xProta = p->getX();
    yProta = p->getY();
}

void IABola::nuevaActitud(float xBola, float yBola)
{
    b2Vec2 puntoI(xBola, yBola);
    b2Vec2 puntoF(xProta, yProta);
    b2Vec2 dist = puntoF - puntoI;

    if (dist.Length() < rangoVision)
    {
        actitud = AGRESIVO;
    }
    else
    {
        actitud = PASIVO;
    }
}

b2Vec2 IABola::nuevaDireccion(float xBola, float yBola)
{
    b2Vec2 puntoI(xBola, yBola);
    b2Vec2 puntoF(xProta, yProta);
    b2Vec2 dir = puntoF - puntoI;

    if (dir.Length() < rangoVision)
    {

    }

    dir.Normalize(); // Devolvemos el vector normalizado
    return dir;
}