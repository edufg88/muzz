#include "ObjetoFijo.h"
#include "InterfazFisica.h"
#include "InterfazAudio.h"
#include "DatosCancion.h"
#include <iostream>
#include <math.h>
using namespace std;

ObjetoFijo::ObjetoFijo(string nombre, float32 x, float32 y):Objeto(nombre, x, y)
{
    animacion = new Animacion();
}

ObjetoFijo::~ObjetoFijo()
{
    if (animacion != NULL)
    {
        delete animacion;
    }
    animacion = NULL;
}

void ObjetoFijo::pintar() const
{
    animacion->getImagen()->drawRot(posX, posY, ZOBJETOESCENARIO, 0);
}

void ObjetoFijo::setPos(float32 x, float32 y)
{
    posX = x;
    posY = y;
}

Animacion* ObjetoFijo::getAnimacion() const
{
    return animacion;
}

void ObjetoFijo::setAnimacion(Animacion* a)
{
    animacion = a;
}
