#include "Objetos/Pico.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"

Pico::Pico(string nombre, float32 x, float32 y) : ObjetoMovil (nombre, x, y)
{
    animacionMov = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMov->getImagen(0)->width();
    alto = animacionMov->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(DINAMICO, this, anchof, altof, 1.0f, 1.0f));
}

Pico::~Pico()
{
    if (animacionMov != NULL)
    {
        delete animacionMov;
    }
    animacionMov = NULL;
}

void Pico::pintar () const
{
    if (visible)
    {
        animacionMov->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
    }
}

void Pico::actualizar()
{
    ObjetoMovil::actualizar();
}

void Pico::inicializarAnimaciones()
{
    wstring ruta = rutaSprite();
    ruta += L"pico.png";
    animacionMov->anyadirImagen(ruta);
}

