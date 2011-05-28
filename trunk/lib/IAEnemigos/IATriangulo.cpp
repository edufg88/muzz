#include "IAEnemigos/IATriangulo.h"
#include "Enemigos/Triangulo.h"
#include "Protagonista.h"
#include "Juego.h"

IATriangulo::IATriangulo()
{
}

IATriangulo::IATriangulo(int actitud) : IAEnemigo(actitud)
{

}

IATriangulo::~IATriangulo()
{

}

void IATriangulo::actualizar()
{
    actualizarPosProta();
}

void IATriangulo::actualizarPosProta()
{
    Protagonista* p = Juego::getInstancia()->getProtagonista();
    xProta = p->getX();
    yProta = p->getY();
}

bool IATriangulo::atacar(int xTriangulo, int yTriangulo) const
{
    bool ataque = false;

    if (actitud == AGRESIVO)
    {
        b2Vec2 distancia (xProta - xTriangulo, yProta - yTriangulo);

        if (distancia.Length() < 200)
            ataque = true;
    }

    return ataque;
}

bool IATriangulo::escapar(int xTriangulo, int yTriangulo) const
{
    bool escape = false;

    if (actitud == EVASIVO)
    {
        b2Vec2 distancia (xProta - xTriangulo, yProta - yTriangulo);

        if (distancia.Length() < 200 )
            escape = true;
    }

    return escape;
}

bool IATriangulo::moverDerecha(int dirTriangulo, int xTriangulo, int yTriangulo) const
{
    bool mover = false;

    if (actitud == AGRESIVO)
    {
        // Si el protagonista se encuentra a la derecha
        if (xProta > xTriangulo)
        {
            // Está lo suficientemente cerca
            if (abs(xProta - xTriangulo) < 200)
            {
                mover = true;
            }
        }
    }
    else if (actitud == EVASIVO)
    {

    }

    return mover;
}

bool IATriangulo::moverIzquierda(int dirTriangulo, int xTriangulo, int yTriangulo) const
{
    bool mover = false;

    if (actitud == AGRESIVO)
    {
        // Si el protagonista se encuentra a la izquierda
        if (xProta < xTriangulo)
        {
            // Está lo suficientemente cerca
            if (abs(xProta - xTriangulo) < 200)
            {
                mover = true;
            }
        }
    }
    else if (actitud == EVASIVO)
    {

    }

    return mover;
}

bool IATriangulo::parar(int dirTriangulo, int xTriangulo, int yTriangulo) const
{
    bool parar = false;

    if (actitud == AGRESIVO)
    {
        if (dirTriangulo != PARADO)
        {
            // Está lejos
            if (abs(xProta - xTriangulo) > 200)
            {
                parar = true;
            }
        }
    }
    else if (actitud == EVASIVO)
    {

    }
    
    return parar;
}

b2Vec2 IATriangulo::nuevaDireccion(float xTriangulo, float yTriangulo)
{
    b2Vec2 puntoI(xTriangulo, yTriangulo);
    b2Vec2 puntoF(xProta, yProta);
    b2Vec2 dir = puntoF - puntoI;

    dir.Normalize(); // Devolvemos el vector normalizado
    return dir;
}