#include "Objetos/Silencio.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"
#include "InterfazAudio.h"

Silencio::Silencio(int tipo, string nombre, float32 x, float32 y) : ObjetoFijo (nombre, x, y)
{
    setTipo(tipo);
    animacion = new Animacion();
    inicializarAnimaciones();

    ancho = animacion->getImagen(0)->width();
    alto = animacion->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(ESTATICO, this, anchof, altof, 1.0f, 1.0f));
}

Silencio::~Silencio()
{
}

void Silencio::ejecutar()
{
    // Cada silencio aplica una pausa al juego de X segundos
    switch (tipo)
    {
        case BLANCA:
            InterfazAudio::getInstancia()->pausar(4);
            break;
        case NEGRA:
            InterfazAudio::getInstancia()->pausar(3);
            break;
        case CORCHEA:
            InterfazAudio::getInstancia()->pausar(2);
            break;
        case SEMICORCHEA:
            InterfazAudio::getInstancia()->pausar(1);
            break;
    }
}

void Silencio::pintar() const
{
    if (visible)
    {
        animacion->getImagen(tipo)->drawRot(posX, posY, ZOBJETOESCENARIO, 0);
    }
}

int Silencio::getTipo() const
{
    return tipo;
}

void Silencio::setTipo(int tipo)
{
    this->tipo = tipo;
}

void Silencio::inicializarAnimaciones()
{
    wstring ruta = L"media/objetos/silencios/";
    wstring rutaF = ruta + L"blanca.png";
    animacion->anyadirImagen(rutaF);
    rutaF = ruta + L"negra.png";
    animacion->anyadirImagen(rutaF);
    rutaF = ruta + L"corchea.png";
    animacion->anyadirImagen(rutaF);
    rutaF = ruta + L"semicorchea.png";
    animacion->anyadirImagen(rutaF);
}