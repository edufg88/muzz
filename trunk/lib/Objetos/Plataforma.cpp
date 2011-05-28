#include "Objetos/Plataforma.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"
#include "DatosCancion.h"
#include "InterfazAudio.h"

Plataforma::Plataforma(string nombre, float32 x, float32 y) : ObjetoFijo(nombre, x, y)
{
    animacion = new Animacion();
    inicializarAnimaciones();

    ancho = animacion->getImagen(0)->width();
    alto = animacion->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(ESTATICO, this, anchof, altof, 1.0f, 1.0f));
}

Plataforma::~Plataforma()
{

}

void Plataforma::pintar() const
{
    if (visible)
    {
        float32 angulo = InterfazAudio::getInstancia()->getDatosCancion()->getPan()*M_PI/4;
        this->getFisica()->SetTransform(getFisica()->GetPosition(), -angulo);
        angulo = angulo * 180 / M_PI;
        animacion->getImagen()->drawRot(posX, posY, ZOBJETOESCENARIO, angulo);
    }
}


void Plataforma::inicializarAnimaciones()
{
    wstring ruta = rutaSprite();
    ruta += L"plataforma.png";
    animacion->anyadirImagen(ruta);
}
