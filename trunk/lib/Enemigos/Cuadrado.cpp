#include "Enemigos/Cuadrado.h"
#include "InterfazFisica.h"
#include "Enemigos/Bola.h"
#include "InterfazAudio.h"
#include "ProcesadorAudio.h"
#include "DatosPartida.h"

int Cuadrado::rangoMov = 50;

Cuadrado::Cuadrado(string nombre, int x, int y) : Enemigo(nombre, x, y, MOVIZQUIERDA, 100, 10)
{
    velocidad = V2;
    animacionMov = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMov->getImagen(0)->width();
    alto = animacionMov->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(DINAMICO, this, anchof, altof, 0.1f, 1.0f, true, true));

    ia = new IACuadrado(AGRESIVO);
}

Cuadrado::~Cuadrado()
{
    if (animacionMov != NULL)
    {
        delete animacionMov;
    }

    animacionMov = NULL;
}

void Cuadrado::pintar() const
{
    if (visible)
    {
        // Dibujamos el personaje
        switch (estado)
        {
            case MOVIZQUIERDA:
                animacionMov->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                break;
            case MOVDERECHA:
                animacionMov->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                break;
            case PARADO:
                animacionMov->getImagen(2)->drawRot(posX, posY, ZPERSONAJE, 0);
                break;
        }

        // Dibujamos la barra de vida
        animacionVida->getImagen(vida/10)->drawRot(posX, posY - alto, ZPERSONAJE, 0);
    }
}

void Cuadrado::actualizar()
{
    ia->actualizar();
    actualizarMovimiento();
    actualizarVelocidad();
    Enemigo::actualizar();
}

void Cuadrado::actualizarVelocidad()
{
    InterfazAudio* a = InterfazAudio::getInstancia();

    int media = a->getMediaBeats(BASSBEAT) + a->getMediaBeats(MIDBEAT) + a->getMediaBeats(HIGHBEAT);
    int beats = a->getNumeroDeBeats(BASSBEAT) + a->getNumeroDeBeats(MIDBEAT) + a->getNumeroDeBeats(HIGHBEAT);

    // cout << "Media: " << media << ", Beats: " << beats << endl;

    if (beats == 0)
    {
        velocidad = V0;
    }
    else if (beats > media*1.5)
    {
        velocidad = V3;
    }
    else if (beats < media/2)
    {
        velocidad = V1;
    }
    else
    {
        velocidad = V2;
    }
}

void Cuadrado::actualizarMovimiento()
{
    IACuadrado* iac = dynamic_cast<IACuadrado*>(ia);

    if (iac->getActitud() == PASIVO)
    {
        switch (estado)
        {
            case MOVIZQUIERDA:
                if (posX < (xInicial - rangoMov))
                {
                    estado = MOVDERECHA;
                }
                else
                {
                    moverIzquierda();
                }
                break;
            case MOVDERECHA:
                if (posX > (xInicial + rangoMov))
                {
                    estado = MOVIZQUIERDA;
                }
                else
                {
                    moverDerecha();
                }
                break;
        }
    }
    else
    {
        switch (estado)
        {
            case MOVIZQUIERDA:
                if (iac->cambiarDireccion(estado, posX, posY))
                {
                    estado = MOVDERECHA;
                }
                else if (iac->parar(estado, posX, posY))
                {
                    estado = PARADO;
                }
                else
                {
                    moverIzquierda();
                }
                break;

            case MOVDERECHA:
                if (iac->cambiarDireccion(estado, posX, posY))
                {
                    estado = MOVIZQUIERDA;
                }
                else if (iac->parar(estado, posX, posY))
                {
                    estado = PARADO;
                }
                else
                {
                    moverDerecha();
                }
                break;

            case PARADO:
                estado = iac->iniciarMovimiento(estado, posX, posY);
                break;
        }
    }
}

void Cuadrado::inicializarAnimaciones()
{
    wstring ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/cuadrado/";

    // Movimiento (es igual cuando se mueve a la izquierda o a la derecha)
    for (int i = 1; i <= 3; i++)
    {
        wstring rutaFinal = ruta + L"cuadrado" + boost::lexical_cast<wstring>(i) + L".png";
        animacionMov->anyadirImagen(rutaFinal);
    }

    ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/vida/";

    // La barra de vida
    for (int i = 0; i <= 10; i++)
    {
        wstring rutaFinal = ruta + L"vidaenemigo" + boost::lexical_cast<wstring>(i*10) + L".png";
        animacionVida->anyadirImagen(rutaFinal);
    }
}

void Cuadrado::moverIzquierda()
{
    b2Vec2 v(-1.0f*velocidad, getFisica()->GetLinearVelocity().y);
    getFisica()->SetLinearVelocity(v);
}

void Cuadrado::moverDerecha()
{
    b2Vec2 v(+1.0f*velocidad, getFisica()->GetLinearVelocity().y);
    getFisica()->SetLinearVelocity(v);
}

