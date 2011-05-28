#include "Enemigos/Gusano.h"
#include "InterfazFisica.h"
#include "IAEnemigos/IAGusano.h"

Gusano::Gusano(string nombre, int x, int y) : Enemigo(nombre, x, y, PARADO, 100, 10)
{
    velocidad = 0;
    animacionMov = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMov->getImagen(0)->width()/3;
    alto = animacionMov->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(DINAMICO, this, anchof, altof, 0.1f, 1.0f, true, true));

    ia = new IAGusano(AGRESIVO);
    IAGusano* iag = dynamic_cast<IAGusano*>(ia);
    iag->setAltoGusano(alto);
}

Gusano::~Gusano ()
{
}

void Gusano::pintar() const
{
    if (visible)
    {
        animacionMov->getImagen()->drawRot(posX, posY, ZPERSONAJE, ConversorFisico::getDegreesFromRadians(fisica->GetAngle()));
    }
}

void Gusano::moverDerecha()
{
//    int angulo = ConversorFisico::getDegreesFromRadians(fisica->GetAngle());
//    if (angulo < 45)
//    {
//        while (angulo < 45)
//        {
//            fisica->SetTransform(fisica->GetPosition(), fisica->GetAngle() + ConversorFisico::getRadiansFromDegrees(10));
//            angulo = ConversorFisico::getDegreesFromRadians(fisica->GetAngle());
//        }
//    }
    b2Vec2 fuerza(1000.0f, 0.0f);
    b2Vec2 fuerza2(-1000.0f, 0.0f);
    b2Vec2 punto = fisica->GetPosition();
    b2Vec2 punto2 = fisica->GetPosition();
    punto.Set(punto.x, punto.y+alto/2-5);
    punto2.Set(punto.x, punto.y-alto/2+5);
    fisica->ApplyForce(fuerza, punto);
    fisica->ApplyForce(fuerza2, punto2);
    cout << "derecha" << endl;
    estado = MOVDERECHA;
}

void Gusano::moverIzquierda()
{
//    int angulo = ConversorFisico::getDegreesFromRadians(fisica->GetAngle());
//    if (angulo > -45)
//    {
//        while (angulo > -45)
//        {
//            fisica->SetTransform(fisica->GetPosition(), fisica->GetAngle() - ConversorFisico::getRadiansFromDegrees(10));
//            angulo = ConversorFisico::getDegreesFromRadians(fisica->GetAngle());
//        }
//    }

    b2Vec2 fuerza(1000.0f, 0.0f);
    b2Vec2 fuerza2(-1000.0f, 0.0f);
    b2Vec2 punto = fisica->GetPosition();
    b2Vec2 punto2 = fisica->GetPosition();
    punto.Set(punto.x, punto.y+alto/2-5);
    punto2.Set(punto.x, punto.y-alto/2+5);
    fisica->ApplyForce(fuerza, punto2);
    fisica->ApplyForce(fuerza2, punto);
    cout << "izquierda" << endl;
    estado = MOVIZQUIERDA;
}

void Gusano::parar()
{
    int angulo = ConversorFisico::getDegreesFromRadians(fisica->GetAngle());

    if (angulo > 0)
    {
        while (angulo > 0)
        {
            fisica->SetTransform(fisica->GetPosition(), fisica->GetAngle() - ConversorFisico::getRadiansFromDegrees(1));
            angulo = ConversorFisico::getDegreesFromRadians(fisica->GetAngle());
        }
    }
    else if (angulo < 0)
    {
        while (angulo < 0)
        {
            fisica->SetTransform(fisica->GetPosition(), fisica->GetAngle() + ConversorFisico::getRadiansFromDegrees(1));
            angulo = ConversorFisico::getDegreesFromRadians(fisica->GetAngle());
        }
    }

    estado = PARADO;
}

void Gusano::actualizar()
{
    ia->actualizar();
    actualizarMovimiento();
    Enemigo::actualizar();
}

void Gusano::inicializarAnimaciones()
{
    wstring ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/enemigos/gusano/gusano.png";

    animacionMov->anyadirImagen(ruta);
}

void Gusano::actualizarMovimiento()
{
    IAGusano* iag = dynamic_cast<IAGusano*>(ia);

    if (iag->moverDerecha(estado, posX, posY))
    {
        moverDerecha();
    }
    else if (iag->moverIzquierda(estado, posX, posY))
    {
        moverIzquierda();
    }
    else if (iag->parar(estado, posX, posY))
    {
        parar();
    }
}