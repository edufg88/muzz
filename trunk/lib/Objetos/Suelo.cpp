#include "Objetos/Suelo.h"
#include "InterfazAudio.h"
#include "DatosCancion.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"

Suelo::Suelo(int tamanyo, string nombre, float32 x, float32 y) : ObjetoFijo (nombre, x, y)
{
    tam = tamanyo;
    animacion = new Animacion();
    inicializarAnimaciones();

    ancho = animacion->getImagen(0)->width();
    alto = animacion->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho - 10);
    float altof = ConversorFisico::getMetersFromPixels(alto - 14);
    setFisica(InterfazFisica::getInstancia()->crearBox(ESTATICO, this, anchof, altof, 1.0f, 1.0f));
}

Suelo::~Suelo()
{

}

void Suelo::pintar() const
{
    if (visible)
    {
        animacion->getImagen()->drawRot(posX, posY, ZOBJETOESCENARIO, 0);
    }
}

void Suelo::inicializarAnimaciones()
{
    wstring ruta = rutaSprite();

    switch (tam)
    {
        case TAM_S:
            ruta += L"suelopequeno.png";
            break;
        case TAM_M:
            ruta += L"suelomedio.png";
            break;
        case TAM_L:
            ruta += L"suelogrande.png";
            break;
        case TAM_XL:
            ruta += L"suelomuygrande.png";
            break;
    }

    animacion->anyadirImagen(ruta);
}

int Suelo::getTam() const
{
    return tam;
}

void Suelo::setTam(int t)
{
    tam = t;
}