#include "IAEnemigos/IAGusano.h"
#include "Enemigos/Gusano.h"
#include "Protagonista.h"
#include "Juego.h"

IAGusano::IAGusano()
{
}

IAGusano::IAGusano(int actitud) : IAEnemigo(actitud)
{

}

IAGusano::~IAGusano()
{

}

void IAGusano::actualizar()
{
    actualizarPosProta();
}

void IAGusano::actualizarPosProta()
{
    Protagonista* p = Juego::getInstancia()->getProtagonista();
    xProta = p->getX();
    yProta = p->getY();
}

bool IAGusano::moverDerecha(int dirGusano, int xGusano, int yGusano) const
{
//    cout << "MOVERDERECHA" << endl;
//    cout << "Gusano(" << xGusano << ", " << yGusano << ")" << endl;
//    cout << "Prota(" << xProta << ", " << yProta << ")" << endl;
//    cout << "Estado: " << dirGusano << endl;
    bool mover = false;

    if (actitud == AGRESIVO)
    {
        if (dirGusano != MOVDERECHA)
        {
            // Si el protagonista se encuentra a la derecha
            if (xProta > xGusano)
            {
                // Está lo suficientemente cerca
                if (abs(xProta - xGusano) < altoGusano/2)
                {
                    mover = true;
                }
            }
        }
    }
    else if (actitud == EVASIVO)
    {

    }

    return mover;
}

bool IAGusano::moverIzquierda(int dirGusano, int xGusano, int yGusano) const
{
//    cout << "MOVERIZQUIERDA" << endl;
//    cout << "Gusano(" << xGusano << ", " << yGusano << ")" << endl;
//    cout << "Prota(" << xProta << ", " << yProta << ")" << endl;
//    cout << "Estado: " << dirGusano << endl;
    bool mover = false;

    if (actitud == AGRESIVO)
    {
        if (dirGusano != MOVIZQUIERDA)
        {
            // Si el protagonista se encuentra a la izquierda
            if (xProta < xGusano)
            {
                // Está lo suficientemente cerca
                if (abs(xProta - xGusano) < altoGusano/2)
                {
                    mover = true;
                }
            }
        }
    }
    else if (actitud == EVASIVO)
    {

    }

    return mover;
}

bool IAGusano::parar(int dirGusano, int xGusano, int yGusano) const
{
//    cout << "PARAR" << endl;
//    cout << "Gusano(" << xGusano << ", " << yGusano << ")" << endl;
//    cout << "Prota(" << xProta << ", " << yProta << ")" << endl;
//    cout << "Estado: " << dirGusano << endl;
//    cout << "ALTO: " << altoGusano << endl;

    bool parar = false;

    if (actitud == AGRESIVO)
    {
        if (dirGusano != PARADO)
        {
            // Está lejos
            if (abs(xProta - xGusano) > altoGusano/2)
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

void IAGusano::setAltoGusano(float alto)
{
    altoGusano = alto;
}