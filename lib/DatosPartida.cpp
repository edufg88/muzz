#include "DatosPartida.h"

DatosPartida* DatosPartida::instancia = NULL;

DatosPartida* DatosPartida::getInstancia()
{
    if (instancia == NULL)
    {
        instancia = new DatosPartida();
    }

    return instancia;
}

DatosPartida::DatosPartida()
{
    vidaPersonaje = 100;
    escudoPersonaje = 100;
    puntos = 0;
}

DatosPartida::~DatosPartida()
{
    instancia = NULL;
    vidaPersonaje = 100;
    escudoPersonaje = 100;
    puntos = 0;
}

void DatosPartida::setVida (int v)
{
    vidaPersonaje = v;

    if (v > 100)
    {
        vidaPersonaje = 100;
    }
    else if (v < 0)
    {
        vidaPersonaje = 0;
    }
}

void DatosPartida::setEscudo (int e)
{
    escudoPersonaje = e;

    if (e > 100)
    {
        escudoPersonaje = 100;
    }
    else if (e < 0)
    {
        escudoPersonaje = 0;
    }
}

void DatosPartida::setPuntos (int p)
{
    puntos = p;

    if (p < 0)
        puntos = 0;
}

void DatosPartida::setEstadoAnimo(int ea)
{
    estadoAnimo = ea;
}

int DatosPartida::getVida () const
{
    return vidaPersonaje;
}

int DatosPartida::getEscudo () const
{
    return escudoPersonaje;
}

int DatosPartida::getPuntos () const
{
    return puntos;
}

int DatosPartida::getEstadoAnimo() const
{
    return estadoAnimo;
}