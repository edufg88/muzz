#include "Enemigos/Bola.h"
#include "InterfazFisica.h"
#include "IAEnemigos/IABola.h"
#include "InterfazAudio.h"
#include "ProcesadorAudio.h"
#include "DatosPartida.h"

int Bola::rangoMov = 100;
  
Bola::Bola(string nombre, int x, int y) : Enemigo(nombre, x, y, MOVIZQUIERDA, 100, 10)
{
    velocidad = VB2;
    animacionMI = new Animacion();
    animacionMD = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMI->getImagen(0)->width();
    alto = animacionMD->getImagen(0)->height();
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearCirculo(CINEMATICO, this, altof/2.0, 1.0f, 1.0f, true));

    ia = new IABola(AGRESIVO);
}

Bola::~Bola()
{
    if (animacionMI != NULL)
    {
        delete animacionMI;
    }
    animacionMI = NULL;
    if (animacionMD != NULL)
    {
        delete animacionMD;
    }
    animacionMD = NULL;
}

void Bola::pintar() const
{
    if (visible)
    {
        switch (estado)
        {
            case MOVLIBREIZQ:
            case MOVIZQUIERDA:
                animacionMI->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                break;
            case MOVLIBREDER:
            case MOVDERECHA:
                animacionMD->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                break;
            default:
                break;
        }

        // Dibujamos la barra de vida
        animacionVida->getImagen(vida/10)->drawRot(posX, posY - alto, ZPERSONAJE, 0);
    }

}

void Bola::actualizarVelocidad()
{
    InterfazAudio* a = InterfazAudio::getInstancia();

    int media = a->getMediaBeats(BASSBEAT) + a->getMediaBeats(MIDBEAT) + a->getMediaBeats(HIGHBEAT);
    int beats = a->getNumeroDeBeats(BASSBEAT) + a->getNumeroDeBeats(MIDBEAT) + a->getNumeroDeBeats(HIGHBEAT);

    // cout << "Media: " << media << ", Beats: " << beats << endl;

    if (beats == 0)
    {
        velocidad = VB0;
    }
    else if (beats > media*1.5)
    {
        velocidad = VB3;
    }
    else if (beats < media/2)
    {
        velocidad = VB1;
    }
    else
    {
        velocidad = VB2;
    }
}

void Bola::actualizarMovimiento()
{
    IABola* iab = dynamic_cast<IABola*>(ia);

    // Actualizamos la actitud si es necesario
    iab->nuevaActitud(posX, posY);

    if (ia->getActitud() == PASIVO)
    {
        switch (estado)
        {
            case MOVARRIBA:
                if (posY < (yInicial - rangoMov))
                {
                    estado = MOVABAJO;
                }
                else
                {
                    moverArriba();
                }
                break;
            case MOVABAJO:
                if (posX > (yInicial + rangoMov))
                {
                    estado = MOVARRIBA;
                }
                else
                {
                    moverAbajo();
                }
                break;
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

            case PARADO:
                break;
        }
    }
    else if (ia->getActitud() == AGRESIVO)
    {
        direccion = iab->nuevaDireccion(posX, posY);
        // Aplicamos el movimiento en esa dirección
        moverDireccion();
    }
    else if (ia->getActitud() == EVASIVO)
    {

    }
    else
    {
        cerr << "ERROR Bola::ActualizarMovimiento, tipo de actitud desconocida" << endl;
    }
}

void Bola::actualizar()
{
    ia->actualizar();
    actualizarMovimiento();
    actualizarVelocidad();
    Enemigo::actualizar();
}

void Bola::moverDireccion()
{
    b2Vec2 v(direccion.x*velocidad, -1.0*direccion.y*velocidad);
    getFisica()->SetLinearVelocity(v);

    if (direccion.x > 0)
    {
        estado = MOVLIBREDER;
    }
    else
    {
        estado = MOVLIBREIZQ;
    }
}

void Bola::moverArriba()
{
    b2Vec2 v( getFisica()->GetLinearVelocity().x, -1.0*velocidad);
    getFisica()->SetLinearVelocity(v);
    estado = MOVARRIBA;
}

void Bola::moverAbajo()
{
    b2Vec2 v( getFisica()->GetLinearVelocity().x, 1.0*velocidad);
    getFisica()->SetLinearVelocity(v);
    estado = MOVABAJO;
}

void Bola::moverIzquierda()
{
    b2Vec2 v(-1.0*velocidad, getFisica()->GetLinearVelocity().y);
    getFisica()->SetLinearVelocity(v);
    estado = MOVIZQUIERDA;
}

void Bola::moverDerecha()
{
    b2Vec2 v(1.0*velocidad, getFisica()->GetLinearVelocity().y);
    getFisica()->SetLinearVelocity(v);
    estado = MOVDERECHA;
}

void Bola::inicializarAnimaciones()
{
    wstring ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/bola/";

    // Movimiento izquierda
    for (int i = 1; i <= 5; i++)
    {
        wstring rutaFinal = ruta + L"movIzquierda/bola" + boost::lexical_cast<wstring>(i) + L".png";
        animacionMI->anyadirImagen(rutaFinal);
    }
    for (int i = 5; i >= 1; i--)
    {
        wstring rutaFinal = ruta + L"movIzquierda/bola" + boost::lexical_cast<wstring>(i) + L".png";
        animacionMI->anyadirImagen(rutaFinal);
    }
    // Movimiento derecha
    for (int i = 1; i <= 5; i++)
    {
        wstring rutaFinal = ruta + L"movDerecha/bola" + boost::lexical_cast<wstring>(i) + L".png";
        animacionMD->anyadirImagen(rutaFinal);
    }
    for (int i = 5; i >= 1; i--)
    {
        wstring rutaFinal = ruta + L"movDerecha/bola" + boost::lexical_cast<wstring>(i) + L".png";
        animacionMD->anyadirImagen(rutaFinal);
    }

    ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/vida/";
    // La barra de vida
    for (int i = 0; i <= 10; i++)
    {
        wstring rutaFinal = ruta + L"vidaenemigo" + boost::lexical_cast<wstring>(i*10) + L".png";
        animacionVida->anyadirImagen(rutaFinal);
    }
}