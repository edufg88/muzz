#include "Enemigos/Triangulo.h"
#include "InterfazFisica.h"
#include "IAEnemigos/IATriangulo.h"
#include "Juego.h"
#include "IAEnemigos/IARueda.h"
#include "IAEnemigos/IABola.h"
#include "DatosPartida.h"

int Triangulo::rangoMov = 100;

Triangulo::Triangulo(string nombre, int x, int y) : Enemigo(nombre, x, y, PARADO, 100, 10)
{
    angulo = 0;
    estado2 = PARADO;
    velocidad = 20;
    velocidadVuelta = 4;
    animacionMI = new Animacion();
    animacionMD = new Animacion();
    animacionPivote = new Animacion();
    xInicial = x;
    yInicial = y;
    inicializarAnimaciones();

    ancho = animacionMI->getImagen(0)->width();
    alto = animacionMD->getImagen(0)->height();

    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(CINEMATICO, this, anchof, altof, 0.1f, 1.0f, true, true));

    ia = new IATriangulo(EVASIVO);
}

Triangulo::~Triangulo ()
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
    if (animacionPivote != NULL)
    {
        delete animacionPivote;
    }
    animacionPivote = NULL;
}

void Triangulo::pintar() const
{
    if (visible)
    {
        animacionPivote->getImagen()->drawRot(xInicial, yInicial, ZPERSONAJE, 0);
        
        switch (estado)
        {
            case MOVLIBREIZQ:
            case MOVIZQUIERDA:
                animacionMI->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, angulo);
                break;
            case MOVLIBREDER:
            case MOVDERECHA:
                animacionMD->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, angulo);
                break;
            case PARADO:
                if (posX < Juego::getInstancia()->getProtagonista()->getX())
                    animacionMD->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, angulo);
                else
                    animacionMI->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, angulo);
            default:
                break;
        }

        // Dibujamos la barra de vida
        animacionVida->getImagen(vida/10)->drawRot(posX, posY - alto, ZPERSONAJE, 0);
    }
}

void Triangulo::atacar()
{
    // Calculamos la nueva dirección de ataque
    float x = Juego::getInstancia()->getProtagonista()->getX();
    float y = Juego::getInstancia()->getProtagonista()->getY();
    b2Vec2 posProta(x, y);
    b2Vec2 posTriangulo(posX, posY);
    direccion = posProta-posTriangulo;
    direccion.Normalize();

    estado2 = ATACANDO;
}

void Triangulo::escapar()
{
    // Calculamos la nueva dirección de evasión
    float x = Juego::getInstancia()->getProtagonista()->getX();
    float y = Juego::getInstancia()->getProtagonista()->getY();
    b2Vec2 posProta(x, y);
    b2Vec2 posTriangulo(posX, posY);
    direccion = posTriangulo-posProta;
    direccion.Normalize();

    estado2 = ESCAPANDO;
}

void Triangulo::volver()
{
    // Calculamos la nueva dirección de ataque
    b2Vec2 posInicial(xInicial, yInicial);
    b2Vec2 posTriangulo(posX, posY);
    direccion = posInicial - posTriangulo;
    direccion.Normalize();

    estado2 = VOLVIENDO;
}

void Triangulo::parar()
{
    direccion.SetZero();
    estado = PARADO;
    estado2 = PARADO;
}

void Triangulo::moverDerecha()
{
    b2Vec2 dist(posX - xInicial, posY - yInicial);

    b2Vec2 v(1.0*velocidad, getFisica()->GetLinearVelocity().y);
    getFisica()->SetLinearVelocity(v);
    estado = MOVDERECHA;
}

void Triangulo::moverIzquierda()
{
    b2Vec2 dist(posX - xInicial, posY - yInicial);

    b2Vec2 v(-1.0*velocidad, getFisica()->GetLinearVelocity().y);
    getFisica()->SetLinearVelocity(v);
    estado = MOVIZQUIERDA;
}

void Triangulo::moverDireccion()
{
    b2Vec2 v;

    // Si está volviendo utilizaremos la velocidad de vuelta
    if (estado2 == VOLVIENDO || estado2 == ESCAPANDO)
    {
        v.Set(direccion.x*velocidadVuelta, -1.0*direccion.y*velocidadVuelta);
    }
    else
    {
        v.Set(direccion.x*velocidad, -1.0*direccion.y*velocidad);
    }

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



void Triangulo::actualizar()
{
    ia->actualizar();
    actualizarMovimiento();
    Enemigo::actualizar();
}

void Triangulo::inicializarAnimaciones()
{
    wstring ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/triangulo/";
    wstring rutaFinal;

    // Movimiento izquierda
    rutaFinal = ruta + L"movIzquierda/triangulo1.png";
    animacionMI->anyadirImagen(rutaFinal);
    rutaFinal = ruta + L"movIzquierda/triangulo2.png";
    animacionMI->anyadirImagen(rutaFinal);
    // Movimiento derecha
    rutaFinal = ruta + L"movDerecha/triangulo1.png";
    animacionMD->anyadirImagen(rutaFinal);
    rutaFinal = ruta + L"movDerecha/triangulo2.png";
    animacionMD->anyadirImagen(rutaFinal);
    // Pivote
    rutaFinal = ruta + L"pivote.png";
    animacionPivote->anyadirImagen(rutaFinal);

    ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/vida/";
    // La barra de vida
    for (int i = 0; i <= 10; i++)
    {
        rutaFinal = ruta + L"vidaenemigo" + boost::lexical_cast<wstring>(i*10) + L".png";
        animacionVida->anyadirImagen(rutaFinal);
    }
}

void Triangulo::actualizarMovimiento()
{
    IATriangulo* iat = dynamic_cast<IATriangulo*>(ia);
    //cout << "(" << posX << ", " << posY << ")  -  " << "Estado: " << estado2 << endl;
    b2Vec2 dist;


    // Calculamos la distancia respecto al pivote, si se sale del rango paramos
    dist.Set(posX-xInicial, posY-yInicial);

    switch (estado2)
    {
        case PARADO:
            volver();
            break;
        case BASE:
            // Solo ataca cuando está en la base
            if (iat->atacar(xInicial, yInicial))
            {
                atacar();
            }
            else if (iat->escapar(xInicial, yInicial))
            {
                escapar();
            }
            break;
        case ATACANDO:
            if (dist.Length() > rangoMov)
            {
                parar();
            }
            break;
        case ESCAPANDO:
            if (dist.Length() > rangoMov)
            {
                parar();
            }
            break;
        case VOLVIENDO:
            if(dist.Length() < 10)
            {
                parar();
                estado2 = BASE;
            }
            break;
    }

    // Actualizamos el ángulo
    if (direccion.x != 0)
    {
        angulo = ConversorFisico::getDegreesFromRadians(atan(direccion.y/direccion.x));
    }

    // Movemos el objeto
    moverDireccion();
}