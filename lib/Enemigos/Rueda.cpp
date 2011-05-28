#include "Enemigos/Rueda.h"
#include "InterfazFisica.h"
#include "IAEnemigos/IARueda.h"
#include "InterfazAudio.h"
#include "ProcesadorAudio.h"
#include "DatosPartida.h"

Rueda::Rueda(string nombre, int x, int y) : Enemigo(nombre, x, y, MOVIZQUIERDA, 100, 10)
{
    rangoMov = 100;
    velocidad = VR2;
    animacionMov = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMov->getImagen(0)->width();
    alto = animacionMov->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    setFisica(InterfazFisica::getInstancia()->crearCirculo(DINAMICO, this, anchof/2, 1.0f, 1.0f));

    ia = new IARueda(PASIVO);
    parar();
    moverIzquierda();
}

Rueda::~Rueda()
{
    if (animacionMov != NULL)
    {
        delete animacionMov;
    }
    
    animacionMov = NULL;
}

void Rueda::pintar() const
{
    if (visible)
    {
        float32 angulo = getFisica()->GetAngle();
        angulo = angulo * 180 / M_PI;
        animacionMov->getImagen()->drawRot(posX, posY, ZPERSONAJE, -angulo);

        // Dibujamos la barra de vida
        animacionVida->getImagen(vida/10)->drawRot(posX, posY - alto, ZPERSONAJE, 0);
    }
}

void Rueda::actualizarVelocidad()
{
    InterfazAudio* a = InterfazAudio::getInstancia();

    int media = a->getMediaBeats(BASSBEAT) + a->getMediaBeats(MIDBEAT) + a->getMediaBeats(HIGHBEAT);
    int beats = a->getNumeroDeBeats(BASSBEAT) + a->getNumeroDeBeats(MIDBEAT) + a->getNumeroDeBeats(HIGHBEAT);

    // cout << "Media: " << media << ", Beats: " << beats << endl;

    if (beats == 0)
    {
        velocidad = VR0;
    }
    else if (beats > media*1.5)
    {
        velocidad = VR3;
    }
    else if (beats < media/2)
    {
        velocidad = VR1;
    }
    else
    {
        velocidad = VR2;
    }
}

void Rueda::actualizar()
{
    ia->actualizar();
    actualizarMovimiento();
    actualizarVelocidad();
    Enemigo::actualizar();
}

void Rueda::moverIzquierda()
{
    b2Vec2 fuerza(-1.0f*velocidad, 0.0f);
    b2Vec2 punto = fisica->GetPosition();
    fisica->ApplyForce(fuerza, punto);
    estado = MOVIZQUIERDA;
}

void Rueda::moverDerecha()
{
    b2Vec2 fuerza(1.0f*velocidad, 0.0f);
    b2Vec2 punto = fisica->GetPosition();
    fisica->ApplyForce(fuerza, punto);
    estado = MOVDERECHA;
}

void Rueda::parar()
{
    b2Vec2 v(0.0f, fisica->GetLinearVelocity().y);
    fisica->SetLinearVelocity(v);
    estado = PARADO;
}

void Rueda::saltar()
{
    b2Vec2 fuerza(fisica->GetLinearVelocity().x, -1.0f*velocidad);
    b2Vec2 punto = fisica->GetPosition();
    fisica->ApplyForce(fuerza, punto);
}

void Rueda::inicializarAnimaciones()
{
    wstring ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/rueda/rueda1.png";
    animacionMov->anyadirImagen(ruta);

    ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/vida/";
    // La barra de vida
    for (int i = 0; i <= 10; i++)
    {
        wstring rutaFinal = ruta + L"vidaenemigo" + boost::lexical_cast<wstring>(i*10) + L".png";
        animacionVida->anyadirImagen(rutaFinal);
    }
}

void Rueda::actualizarMovimiento()
{
    IARueda* iar = dynamic_cast<IARueda*>(ia);

    // Comprobamos si hay que saltar
    if (iar->saltar(estado, posX, posY))
    {
        //saltar();
    }

    if (iar->getActitud() == PASIVO)
    {
        switch (estado)
        {
            case MOVIZQUIERDA:
                if (posX < (xInicial - rangoMov))
                {
                    estado = MOVDERECHA;
                    parar();
                    moverDerecha();
                }
                break;
            case MOVDERECHA:
                if (posX > (xInicial + rangoMov))
                {
                    estado = MOVIZQUIERDA;
                    parar();
                    moverIzquierda();
                }
                break;
        }
    }
    else
    {
        switch (estado)
        {
            case MOVIZQUIERDA:
                if (iar->cambiarDireccion(estado, posX, posY))
                {
                    estado = MOVDERECHA;
                    parar();
                    moverDerecha();
                }
                else if (iar->parar(estado, posX, posY))
                {
                    estado = PARADO;
                    parar();
                    fisica->SetAngularVelocity(0.0f);
                }
                else
                {
                    parar();
                    moverIzquierda();
                }
                break;

            case MOVDERECHA:
                if (iar->cambiarDireccion(estado, posX, posY))
                {
                    estado = MOVIZQUIERDA;
                    parar();
                    moverIzquierda();
                }
                else if (iar->parar(estado, posX, posY))
                {
                    estado = PARADO;
                    parar();
                    fisica->SetAngularVelocity(0.0f);
                }
                else
                {
                    parar();
                    moverDerecha();
                }
                break;

            case PARADO:
                estado = iar->iniciarMovimiento(estado, posX, posY);
                break;
        }
    }
}