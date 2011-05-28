#include "Objetos/BloqueSimetrico.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"
#include "InterfazAudio.h"
#include "ProcesadorAudio.h"
#include <Box2D/Box2D.h>

int BloqueSimetrico::rangoMovimiento = 100;

BloqueSimetrico::BloqueSimetrico (int dir, string nombre, float32 x, float32 y) : ObjetoMovil (nombre, x, y)
{
    xInicial = x;
    yInicial = y;

    velocidad = BSV2;
    direccion = dir;
    simetrico = NULL;
    animacionMov = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMov->getImagen(0)->width();
    alto = animacionMov->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(CINEMATICO, this, anchof, altof, 1.0f, 1.0f));
}

BloqueSimetrico::~BloqueSimetrico()
{
    if (animacionMov != NULL)
    {
        delete animacionMov;
    }
    animacionMov = NULL;
}

void BloqueSimetrico::pintar () const
{
    if (visible)
    {
        animacionMov->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
    }
}

void BloqueSimetrico::actualizar()
{
    ObjetoMovil::actualizar();
    actualizarMovimiento();
    actualizarVelocidad();
}

void BloqueSimetrico::actualizarVelocidad()
{
    InterfazAudio* a = InterfazAudio::getInstancia();

    int media = a->getMediaBeats(BASSBEAT) + a->getMediaBeats(MIDBEAT) + a->getMediaBeats(HIGHBEAT);
    int beats = a->getNumeroDeBeats(BASSBEAT) + a->getNumeroDeBeats(MIDBEAT) + a->getNumeroDeBeats(HIGHBEAT);

    // cout << "Media: " << media << ", Beats: " << beats << endl;

    if (beats == 0)
    {
        velocidad = BSV0;
    }
    else if (beats > media*1.5)
    {
        velocidad = BSV3;
    }
    else if (beats < media/2)
    {
        velocidad = BSV1;
    }
    else
    {
        velocidad = BSV2;
    }
}

void BloqueSimetrico::actualizarMovimiento()
{
    b2Vec2 v;
    
    switch (direccion)
    {
        case ARRIBA:
            // Si es el que está abajo
            if (simetrico->getY() < posY)
            {
                if (posY < yInicial)
                {
                    cambiarDireccion();
                }
            }
            // Si es el que está arriba
            else
            {
                if (abs(yInicial - posY) > rangoMovimiento)
                {
                    cambiarDireccion();
                }
            }
            break;
        case ABAJO:
            // Si es el que está abajo
            if (simetrico->getY() < posY)
            {
                if (abs(yInicial - posY) > rangoMovimiento)
                {
                    cambiarDireccion();
                }
            }
            // Si es el que está arriba
            else
            {
                if (posY > yInicial)
                {
                    cambiarDireccion();
                }
            }
            break;
        case IZQUIERDA:
            // Si es el que está a la izquierda
            if (simetrico->getX() > posX)
            {
                if (abs(xInicial - posX) > rangoMovimiento)
                {
                    cambiarDireccion();
                }
            }
            // Si es el que está a la derecha
            else
            {
                if (posX < xInicial)
                {
                    cambiarDireccion();
                }
            }
            break;
        case DERECHA:
            // Si es el que está a la izquierda
            if (simetrico->getX() > posX)
            {
                if (posX > xInicial)
                {
                    cambiarDireccion();
                }
            }
            // Si es el que está a la derecha
            else
            {
                if (abs(xInicial - posX) > rangoMovimiento)
                {
                    cambiarDireccion();
                }
            }
            break;
    }

    switch (direccion)
    {
        case ARRIBA:
            v.Set(0.0f, 1*velocidad);
            fisica->SetLinearVelocity(v);
            break;
        case ABAJO:
            v.Set(0.0f, -1*velocidad);
            fisica->SetLinearVelocity(v);
            break;
        case IZQUIERDA:
            v.Set(-1*velocidad, 0.0f);
            fisica->SetLinearVelocity(v);
            break;
        case DERECHA:
            v.Set(1*velocidad, 0.0f);
            fisica->SetLinearVelocity(v);
            break;
    }
}

void BloqueSimetrico::inicializarAnimaciones()
{
    wstring ruta = rutaSprite();
    ruta += L"bloquesimetrico.png";
    animacionMov->anyadirImagen(ruta);
}

int BloqueSimetrico::getDireccion() const
{
    return direccion;
}

void BloqueSimetrico::setDireccion(int dir)
{
    direccion = dir;
}

void BloqueSimetrico::cambiarDireccion()
{
    if (direccion == ARRIBA)
    {
        direccion = ABAJO;
    }
    else if (direccion == ABAJO)
    {
        direccion = ARRIBA;
    }
    else if (direccion == IZQUIERDA)
    {
        direccion = DERECHA;
    }
    else if (direccion == DERECHA)
    {
        direccion = IZQUIERDA;
    }
}

void BloqueSimetrico::setSimetrico(BloqueSimetrico* sim)
{
    simetrico = sim;
}

void BloqueSimetrico::abrir()
{

}

void BloqueSimetrico::cerrar()
{

}

void BloqueSimetrico::parar()
{
    b2Vec2 v(0.0f, 0.0f);
    fisica->SetLinearVelocity(v);
    direccion = PARADO;
}