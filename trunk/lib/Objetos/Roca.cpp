#include "Objetos/Roca.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"

Roca::Roca(string nombre, float32 x, float32 y) : ObjetoMovil (nombre, x, y)
{
    animacionMov = new Animacion();
    inicializarAnimaciones();
    
    ancho = animacionMov->getImagen(0)->width();
    alto = animacionMov->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    setFisica(InterfazFisica::getInstancia()->crearCirculo(DINAMICO, this, anchof/2, 1.0f, 1.0f));
}

Roca::~Roca()
{
    if (animacionMov != NULL)
    {
        delete animacionMov;
    }
    animacionMov = NULL;
}

void Roca::pintar () const
{
    if (visible)
    {
        float32 angulo = getFisica()->GetAngle();
        angulo = angulo * 180 / M_PI;
        animacionMov->getImagen()->drawRot(posX, posY, ZOBJETOESCENARIO, -angulo);
    }
}

void Roca::actualizar()
{
    ObjetoMovil::actualizar();
}

void Roca::inicializarAnimaciones()
{
    wstring ruta = rutaSprite();
    ruta += L"roca.png";
    animacionMov->anyadirImagen(ruta);
}

