#include "IAEnemigos/IACuadrado.h"
#include "Juego.h"
#include <math.h>

IACuadrado::IACuadrado() : IAEnemigo()
{
}

IACuadrado::IACuadrado(int actitud) : IAEnemigo(actitud)
{
}

IACuadrado::~IACuadrado()
{

}

void IACuadrado::actualizar()
{
    actualizarPosProta();
}

void IACuadrado::actualizarPosProta()
{
    Protagonista* p = Juego::getInstancia()->getProtagonista();
    xProta = p->getX();
    yProta = p->getY();
}

void IACuadrado::setPosSuelo(float x, float y)
{
    xSuelo = x;
    ySuelo = y;
}

void IACuadrado::setAnchoSuelo(int ancho)
{
    anchoSuelo = ancho;
}

bool IACuadrado::cambiarDireccion(int dirCuadrado,float xCuadrado, float yCuadrado) const
{
    bool cambio = false;
    // Direccion que lleva el protagonista
    int dirProta = Juego::getInstancia()->getProtagonista()->getDireccion();


    if (actitud == EVASIVO)
    {
        switch (dirProta)
        {
            case IZQUIERDA:
                if (dirCuadrado == MOVIZQUIERDA)
                {
                    // El prota esta por encima del cuadrado
                    if ((yCuadrado - yProta) > 50)
                    {
                        // Están bastante cerca
                        if (abs(xProta - xCuadrado) < 50)
                        {
                            cambio = true;
                        }
                    }
                    // El prota se encuentra en la misma superficie que el cuadrado
                    else
                    {
                        // El prota esta a la izquierda del cuadrado
                        if (xProta < xCuadrado)
                        {
                            cambio = true;
                        }
                    }
                }
                else if (dirCuadrado == MOVDERECHA)
                {
                    // El prota se encuentra en la misma superficie que el cuadrado
                    if ((yProta - yCuadrado) < 50)
                    {
                        // El prota esta a la derecha del cuadrado
                        if (xProta > xCuadrado)
                        {
                            cambio = true;
                        }
                    }
                }
                break;

            case DERECHA:
                if (dirCuadrado == MOVDERECHA)
                {
                    // El prota esta por encima del cuadrado
                    if ((yCuadrado - yProta) > 50)
                    {
                        // Están bastante cerca
                        if (abs(xProta - xCuadrado) < 50)
                        {
                            cambio = true;
                        }
                    }
                    // El prota se encuentra en la misma superficie que el cuadrado
                    else
                    {
                        // El prota esta a la derecha del cuadrado
                        if (xProta > xCuadrado)
                        {
                            cambio = true;
                        }
                    }
                }
                else if (dirCuadrado == MOVIZQUIERDA)
                {
                    // El prota se encuentra en la misma superficie que el cuadrado
                    if ((yProta - yCuadrado) < 50)
                    {
                        // El prota esta a la izquierda del cuadrado
                        if (xProta < xCuadrado)
                        {
                            cambio = true;
                        }
                    }
                }
                break;
        }
    }
    else if (actitud == AGRESIVO)
    {
        switch (dirProta)
        {
            case IZQUIERDA:
                if (dirCuadrado == MOVIZQUIERDA)
                {
                    // El prota se encuentra en la misma superficie que el cuadrado
                    if ((yCuadrado - yProta) < 50)
                    {
                        // El prota esta a la derecha del cuadrado
                        if (xProta > xCuadrado)
                        {
                            cambio = true;
                        }
                    }
                }
                else if (dirCuadrado == MOVDERECHA)
                {
                    // El prota está por encima
                    if ((yProta - yCuadrado) > 50)
                    {
                        // Están relativamente cerca
                        if (abs(xProta - xCuadrado) < 50)
                        {
                            cambio = true;
                        }
                    }
                    // El prota está en la misma superficie
                    else
                    {
                        // Si el prota esta a la izquierda
                        if (xProta < xCuadrado)
                        {
                            cambio = true;
                        }
                    }
                }
                break;

            case DERECHA:
                if (dirCuadrado == MOVDERECHA)
                {
                    // El prota se encuentra en la misma superficie que el cuadrado
                    if ((yCuadrado - yProta) < 50)
                    {
                        // El prota esta a la izquierda del cuadrado
                        if (xProta < xCuadrado)
                        {
                            cambio = true;
                        }
                    }
                }
                else if (dirCuadrado == MOVIZQUIERDA)
                {
                    // El prota está por encima
                    if ((yProta - yCuadrado) > 50)
                    {
                        // Están relativamente cerca
                        if (abs(xProta - xCuadrado) < 50)
                        {
                            cambio = true;
                        }
                    }
                    // El prota está en la misma superficie
                    else
                    {
                        // Si el prota esta a la derecha
                        if (xProta > xCuadrado)
                        {
                            cambio = true;
                        }
                    }
                }
                break;
        }
    }
    else if (actitud == PASIVO)
    {
        if (dirCuadrado == MOVIZQUIERDA)
        {
            // Comprobamos si esta dentro de su rango de movimiento
        }
        else if (dirCuadrado == MOVDERECHA)
        {

        }
    }
    else
    {
        cerr << "ERROR IACuadrado::CambiarDireccion:  actitud desconocida" << endl;
    }

//    cout << "Cuadrado: " << "(" << xCuadrado << "," << yCuadrado << ")" << endl;
//    cout << "Prota: " << "(" << Juego::getInstancia()->getProtagonista()->getX() << "," << Juego::getInstancia()->getProtagonista()->getY() << ")" << endl;

    return cambio;
}

bool IACuadrado::parar(int dirCuadrado,float xCuadrado, float yCuadrado) const
{
    bool parar = false;
    // Direccion que lleva el protagonista
    int dirProta = Juego::getInstancia()->getProtagonista()->getDireccion();

    if (actitud == EVASIVO)
    {
        if (dirCuadrado == MOVIZQUIERDA)
        {
            // Si está muy cerca del borde
            if ((xCuadrado - (xSuelo - anchoSuelo/2)) < 50)
            {
                parar = true;
            }
        }
        else if (dirCuadrado == MOVDERECHA)
        {
            if (((xSuelo + anchoSuelo/2) - xCuadrado) < 50)
            {
                parar = true;
            }
        }
    }
    else if (actitud == AGRESIVO)
    {
        if (dirCuadrado == MOVIZQUIERDA)
        {
            // Si está muy cerca del borde
            if ((xCuadrado - (xSuelo - anchoSuelo/2)) < 50)
            {
                parar = true;
            }
        }
        else if (dirCuadrado == MOVDERECHA)
        {
            if (((xSuelo + anchoSuelo/2) - xCuadrado) < 50)
            {
                parar = true;
            }
        }
    }
    else if (actitud == PASIVO)
    {

    }
    else
    {
        cerr << "ERROR IACuadrado::Parar:  actitud desconocida" << endl;
    }

    //cout << "PARAR: " << parar << endl << "............." << endl;

    return parar;
}

int IACuadrado::iniciarMovimiento(int dirCuadrado,float xCuadrado, float yCuadrado) const
{
    
    //cout << "Cuadrado: " << "(" << xCuadrado << "," << yCuadrado << ")" << endl;
    //cout << "Prota: " << "(" << Juego::getInstancia()->getProtagonista()->getX() << "," << Juego::getInstancia()->getProtagonista()->getY() << ")" << endl;


    int movimiento = PARADO;
    // Direccion que lleva el protagonista
    int dirProta = Juego::getInstancia()->getProtagonista()->getDireccion();

    if (actitud == EVASIVO)
    {
        // Si está muy cerca del borde izquierdo
        if ((xCuadrado - (xSuelo - anchoSuelo/2)) < 50)
        {
            // El prota esta por encima del cuadrado
            if ((yCuadrado - yProta) > 50)
            {
                // Están bastante cerca
                if (abs(xProta - xCuadrado) < 50)
                {
                    movimiento = MOVDERECHA;
                }
            }
        }
        // Si está muy cerca del borde derecho
        else if (((xSuelo + anchoSuelo/2) - xCuadrado) < 50)
        {
            // El prota esta por encima del cuadrado
            if ((yCuadrado - yProta) > 50)
            {
                // Están bastante cerca
                if (abs(xProta - xCuadrado) < 50)
                {
                    movimiento = MOVIZQUIERDA;
                }
            }
        }
        // Está parado en un sitio más o menos intermedio
        else
        {
            if (dirProta == DERECHA)
            {
                // El prota está a la izquierda del cuadrado
                if (xProta < xCuadrado)
                {
                    movimiento = MOVDERECHA;
                }
            }
            else if (dirProta == IZQUIERDA)
            {
                // El prota está a la derecha del cuadrado
                if (xProta > xCuadrado)
                {
                    movimiento = MOVIZQUIERDA;
                }
            }
        }
    }
    else if (actitud == AGRESIVO)
    {
        // Si está muy cerca del borde izquierdo
        if ((xCuadrado - (xSuelo - anchoSuelo/2)) < 50)
        {
            // El prota esta por encima del cuadrado
            if ((yCuadrado - yProta) > 50)
            {
                // Están bastante cerca
                if (abs(xProta - xCuadrado) < 50)
                {
                    movimiento = MOVDERECHA;
                }
            }
        }
        // Si está muy cerca del borde derecho
        else if (((xSuelo + anchoSuelo/2) - xCuadrado) < 50)
        {
            // El prota esta por encima del cuadrado
            if ((yCuadrado - yProta) > 50)
            {
                // Están bastante cerca
                if (abs(xProta - xCuadrado) < 50)
                {
                    movimiento = MOVIZQUIERDA;
                }
            }
        }
        // Está parado en un sitio más o menos intermedio
        else
        {
            if (dirProta == DERECHA)
            {
                // El prota está a la izquierda del cuadrado
                if (xProta < xCuadrado)
                {
                    movimiento = MOVIZQUIERDA;
                }
            }
            else if (dirProta == IZQUIERDA)
            {
                // El prota está a la derecha del cuadrado
                if (xProta > xCuadrado)
                {
                    movimiento = MOVDERECHA;
                }
            }
        }
    }
    else if (actitud == PASIVO)
    {

    }
    else
    {
        cerr << "ERROR IACuadrado::Parar:  actitud desconocida" << endl;
    }

//    cout << "INICIAR MOV: " << endl;
//    cout << "Movimiento: " << movimiento << endl << "............." << endl;
    return movimiento;
}