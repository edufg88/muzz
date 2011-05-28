#include "Objetos/Pinchos.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"

Pinchos::Pinchos(int num, string nombre, float32 x, float32 y) : ObjetoMovil (nombre, x, y)
{
    numero = num;
    animacionMov = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMov->getImagen(0)->width()*numero;
    alto = animacionMov->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(CINEMATICO, this, anchof, altof, 1.0f, 1.0f));
}

Pinchos::~Pinchos()
{
    if (animacionMov != NULL)
    {
        delete animacionMov;
    }
    animacionMov = NULL;
}

void Pinchos::pintar () const
{
    if (visible)
    {
        for (int i = 0; i < numero; i++)
        {
            animacionMov->getImagen()->drawRot(posX + ((i-2)*ancho/numero), posY, ZPERSONAJE, 0);
        }
    }
}

void Pinchos::actualizar()
{
    ObjetoMovil::actualizar();
}

void Pinchos::inicializarAnimaciones()
{
    wstring ruta = rutaSprite();
    ruta += L"pincho.png";
    animacionMov->anyadirImagen(ruta);
}

