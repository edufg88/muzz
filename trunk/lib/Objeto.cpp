#include "Objeto.h"
#include "Juego.h"
#include "ConversorFisico.h"
#include "DatosCancion.h"

Objeto::Objeto(string pNombre, float32 x, float32 y)
{
    nombre = pNombre;
    posX = x;
    posY = y;
    this->setVisible(true);
    this->setActivo(true);
}

Objeto::~Objeto()
{
    // El propio objeto destruye su cuerpo físico
    InterfazFisica::getInstancia()->getMundo()->DestroyBody(fisica);
}

void Objeto::actualizar()
{
    setPos(ConversorFisico::getPixelsFromMeters(fisica->GetPosition().x), (-1)*ConversorFisico::getPixelsFromMeters(fisica->GetPosition().y));
}

void Objeto::setPos(float32 x, float32 y)
{
    posX = x;
    posY = y;
}

float32 Objeto::getX() const
{
    return posX;
}

float32 Objeto::getY() const
{
    return posY;
}

bool Objeto::esVisible() const
{
    return visible;
}

void Objeto::setVisible(bool vis)
{
    visible = vis;
}

bool Objeto::esActivo() const
{
    return activo;
}

void Objeto::setActivo(bool act)
{
    activo = act;
}

b2Body* Objeto::getFisica() const
{
    return fisica;
}

void Objeto::setFisica(b2Body* f)
{
    fisica = f;
}

float32 Objeto::getAncho() const
{
    return ancho;
}

float32 Objeto::getAlto() const
{
    return alto;
}

void Objeto::setAncho(float32 pAncho)
{
    ancho = pAncho;
}

void Objeto::setAlto(float32 pAlto)
{
    alto = pAlto;
}

string Objeto::getNombre() const
{
    return nombre;
}

void Objeto::setNombre(string pNombre)
{
    nombre = pNombre;
}

wstring Objeto::rutaSprite()
{
    // Primero obtenemos el género para cargar la imagen en funcion
    int genero = InterfazAudio::getInstancia()->getDatosCancion()->getGenero();

    wstring ruta = Gosu::sharedResourcePrefix() + L"media/objetos/";

    switch (genero)
    {
        case BLUES:
        case JAZZ:
        case R_AND_B:
        case SOUL:
            ruta += L"blues-jazz-rnb-soul/";
            break;

        case CLASSICAL:
        case CHILL_OUT:
            ruta += L"classical-chillout/";
            break;

        case DANCE:
        case DISCO:
        case FUNK:
        case POP:
            ruta += L"dance-disco-funk-pop/";
            break;

        case PUNK:
        case METAL:
        case ROCK:
            ruta += L"punk-metal-rock/";
            break;

        case RAP:
        case REGGAE:
        case LATIN:
            ruta += L"rap-reggae-latin/";
            break;

        case TECHNO:
        case SKA:
        case HOUSE:
            ruta += L"techno-ska-house/";
            break;

        default:
            break;
    }

    return ruta;
}