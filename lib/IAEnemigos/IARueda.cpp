#include "IAEnemigos/IARueda.h"
#include "Juego.h"

IARueda::IARueda()
{

}

IARueda::IARueda(int actitud) : IAEnemigo(actitud)
{

}

IARueda::~IARueda()
{

}

void IARueda::actualizar()
{
    actualizarPosProta();
}

void IARueda::actualizarPosProta()
{
    Protagonista* p = Juego::getInstancia()->getProtagonista();
    xProta = p->getX();
    yProta = p->getY();
}

void IARueda::setPosSuelo(float x, float y)
{
    xSuelo = x;
    ySuelo = y;
}

void IARueda::setAnchoSuelo(int ancho)
{
    anchoSuelo = ancho;
}

bool IARueda::cambiarDireccion(int dirRueda, float xRueda, float yRueda) const
{
    bool cambio = false;
    // Direccion que lleva el protagonista
    int dirProta = Juego::getInstancia()->getProtagonista()->getDireccion();

    if (actitud == EVASIVO)
    {
        switch (dirProta)
        {
            case IZQUIERDA:
                if (dirRueda == MOVIZQUIERDA)
                {
                    // El prota esta por encima del rueda
                    if ((yRueda - yProta) > 50)
                    {
                        // Están bastante cerca
                        if (abs(xProta - xRueda) < 50)
                        {
                            cambio = true;
                        }
                    }
                    // El prota se encuentra en la misma superficie que el rueda
                    else
                    {
                        // El prota esta a la izquierda del rueda
                        if (xProta < xRueda)
                        {
                            cambio = true;
                        }
                    }
                }
                else if (dirRueda == MOVDERECHA)
                {
                    // El prota se encuentra en la misma superficie que el rueda
                    if ((yProta - yRueda) < 50)
                    {
                        // El prota esta a la derecha del rueda
                        if (xProta > xRueda)
                        {
                            cambio = true;
                        }
                    }
                }
                break;

            case DERECHA:
                if (dirRueda == MOVDERECHA)
                {
                    // El prota esta por encima del rueda
                    if ((yRueda - yProta) > 50)
                    {
                        // Están bastante cerca
                        if (abs(xProta - xRueda) < 50)
                        {
                            cambio = true;
                        }
                    }
                    // El prota se encuentra en la misma superficie que el rueda
                    else
                    {
                        // El prota esta a la derecha del rueda
                        if (xProta > xRueda)
                        {
                            cambio = true;
                        }
                    }
                }
                else if (dirRueda == MOVIZQUIERDA)
                {
                    // El prota se encuentra en la misma superficie que el rueda
                    if ((yProta - yRueda) < 50)
                    {
                        // El prota esta a la izquierda del rueda
                        if (xProta < xRueda)
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
                if (dirRueda == MOVIZQUIERDA)
                {
                    // El prota se encuentra en la misma superficie que el rueda
                    if (abs(yRueda - yProta) < 50)
                    {
                        // El prota esta a la derecha del rueda
                        if (xProta > xRueda)
                        {
                            cambio = true;
                        }
                    }
                }
                else if (dirRueda == MOVDERECHA)
                {
                    // El prota está por encima
                    if (abs(yProta - yRueda) > 50)
                    {
                        // Están relativamente cerca
                        if (abs(xProta - xRueda) < 50)
                        {
                            cambio = true;
                        }
                    }
                    // El prota está en la misma superficie
                    else
                    {
                        // Si el prota esta a la izquierda
                        if (xProta < xRueda)
                        {
                            cambio = true;
                        }
                    }
                }
                break;

            case DERECHA:
                if (dirRueda == MOVDERECHA)
                {
                    // El prota se encuentra en la misma superficie que el rueda
                    if (abs(yRueda - yProta) < 50)
                    {
                        // El prota esta a la izquierda del rueda
                        if (xProta < xRueda)
                        {
                            cambio = true;
                        }
                    }
                }
                else if (dirRueda == MOVIZQUIERDA)
                {
                    // El prota está por encima
                    if (abs(yProta - yRueda) > 50)
                    {
                        // Están relativamente cerca
                        if (abs(xProta - xRueda) < 50)
                        {
                            cambio = true;
                        }
                    }
                    // El prota está en la misma superficie
                    else
                    {
                        // Si el prota esta a la derecha
                        if (xProta > xRueda)
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
        if (dirRueda == MOVIZQUIERDA)
        {
            // Comprobamos si esta dentro de su rango de movimiento
        }
        else if (dirRueda == MOVDERECHA)
        {

        }
    }
    else
    {
        cerr << "ERROR IARueda::CambiarDireccion:  actitud desconocida" << endl;
    }

    return cambio;
}

bool IARueda::parar(int dirRueda, float xRueda, float yRueda) const
{
    bool parar = false;
    // Direccion que lleva el protagonista
    int dirProta = Juego::getInstancia()->getProtagonista()->getDireccion();

    if (actitud == EVASIVO)
    {
        if (dirRueda == MOVIZQUIERDA)
        {
            // Si está muy cerca del borde
            if ((xRueda - (xSuelo - anchoSuelo/2)) < 50)
            {
                parar = true;
            }
        }
        else if (dirRueda == MOVDERECHA)
        {
            if (((xSuelo + anchoSuelo/2) - xRueda) < 50)
            {
                parar = true;
            }
        }
    }
    else if (actitud == AGRESIVO)
    {
        if (dirRueda == MOVIZQUIERDA)
        {
            // Si está muy cerca del borde
            if ((xRueda - (xSuelo - anchoSuelo/2)) < 50)
            {
                parar = true;
            }
        }
        else if (dirRueda == MOVDERECHA)
        {
            if (((xSuelo + anchoSuelo/2) - xRueda) < 50)
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
        cerr << "ERROR IARueda::Parar:  actitud desconocida" << endl;
    }

    return parar;
}

bool IARueda::saltar(int dirRueda, float xRueda, float yRueda) const
{

}

int IARueda::iniciarMovimiento(int dirRueda, float xRueda, float yRueda) const
{
    int movimiento = PARADO;
    // Direccion que lleva el protagonista
    int dirProta = Juego::getInstancia()->getProtagonista()->getDireccion();

    if (actitud == EVASIVO)
    {
        // Si está muy cerca del borde izquierdo
        if ((xRueda - (xSuelo - anchoSuelo/2)) < 50)
        {
            // El prota esta por encima del rueda
            if ((yRueda - yProta) > 50)
            {
                // Están bastante cerca
                if (abs(xProta - xRueda) < 50)
                {
                    movimiento = MOVDERECHA;
                }
            }
        }
        // Si está muy cerca del borde derecho
        else if (((xSuelo + anchoSuelo/2) - xRueda) < 50)
        {
            // El prota esta por encima del rueda
            if ((yRueda - yProta) > 50)
            {
                // Están bastante cerca
                if (abs(xProta - xRueda) < 50)
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
                // El prota está a la izquierda del rueda
                if (xProta < xRueda)
                {
                    movimiento = MOVDERECHA;
                }
            }
            else if (dirProta == IZQUIERDA)
            {
                // El prota está a la derecha del Rueda
                if (xProta > xRueda)
                {
                    movimiento = MOVIZQUIERDA;
                }
            }
        }
    }
    else if (actitud == AGRESIVO)
    {
        // Si está muy cerca del borde izquierdo
        if ((xRueda - (xSuelo - anchoSuelo/2)) < 50)
        {
            // El prota esta por encima del rueda
            if ((yRueda - yProta) > 50)
            {
                // Están bastante cerca
                if (abs(xProta - xRueda) < 50)
                {
                    movimiento = MOVDERECHA;
                }
            }
        }
        // Si está muy cerca del borde derecho
        else if (((xSuelo + anchoSuelo/2) - xRueda) < 50)
        {
            // El prota esta por encima del rueda
            if ((yRueda - yProta) > 50)
            {
                // Están bastante cerca
                if (abs(xProta - xRueda) < 50)
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
                // El prota está a la izquierda del rueda
                if (xProta < xRueda)
                {
                    movimiento = MOVIZQUIERDA;
                }
            }
            else if (dirProta == IZQUIERDA)
            {
                // El prota está a la derecha del rueda
                if (xProta > xRueda)
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
        cerr << "ERROR IARueda::Parar:  actitud desconocida" << endl;
    }

    return movimiento;
}