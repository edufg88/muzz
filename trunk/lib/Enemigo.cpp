#include "Enemigo.h"
#include "DatosPartida.h"

Enemigo::Enemigo(string nombre, int x, int y, int pEstado, int pVida, int pDanyo) : ObjetoMovil(nombre, x, y)
{
    estado = pEstado;
    vida = pVida;
    danyo = pDanyo;
    xInicial = x;
    yInicial = y;
    animacionVida = new Animacion();
}

Enemigo::~Enemigo()
{
    if (ia != NULL)
    {
        delete ia;
    }
    ia = NULL;
}

int Enemigo::getEstado() const
{
    return estado;
}

int Enemigo::getVida() const
{
    return vida;
}

int Enemigo::getDanyo() const
{
    return danyo;
}

IAEnemigo* Enemigo::getIA() const
{
    return ia;
}

void Enemigo::sufrirDanyo(int danyo)
{
    vida -= danyo;
    
    if (vida <= 0)
    {
        this->setActivo(false);

        if (nombre == "bola")
        {
            DatosPartida::getInstancia()->setPuntos(DatosPartida::getInstancia()->getPuntos() + 300);
        }
        else if (nombre == "rueda")
        {
            DatosPartida::getInstancia()->setPuntos(DatosPartida::getInstancia()->getPuntos() + 200);
        }
        else if (nombre == "cuadrado")
        {
            DatosPartida::getInstancia()->setPuntos(DatosPartida::getInstancia()->getPuntos() + 100);
        }
        else if (nombre == "triangulo")
        {
            DatosPartida::getInstancia()->setPuntos(DatosPartida::getInstancia()->getPuntos() + 400);
        }
    }
}

void Enemigo::pintar() const
{

}

void Enemigo::actualizar()
{
    ObjetoMovil::actualizar();    
}

