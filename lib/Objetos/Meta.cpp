#include "Objetos/Meta.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"
#include "DatosPartida.h"

Meta::Meta(string nombre, float32 x, float32 y) : ObjetoFijo(nombre, x, y)
{
    animacion = new Animacion();
    inicializarAnimaciones();

    ancho = animacion->getImagen(0)->width();
    alto = animacion->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(ESTATICO, this, anchof, altof, 1.0f, 1.0f));
}

Meta::~Meta()
{

}

void Meta::ejecutar()
{
    DatosPartida::getInstancia()->setPuntos(DatosPartida::getInstancia()->getPuntos() + 100);
}

void Meta::pintar() const
{
    if (visible)
    {
        animacion->getImagen()->drawRot(posX, posY, ZOBJETOESCENARIO, 0);
    }
}

void Meta::inicializarAnimaciones()
{
    wstring ruta = L"media/objetos/otros/";
    ruta += L"meta.png";
    animacion->anyadirImagen(ruta);
}