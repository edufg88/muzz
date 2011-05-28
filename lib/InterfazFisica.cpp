#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include "InterfazFisica.h"
#include "InterfazAudio.h"
#include "DatosCancion.h"
#include "ConversorFisico.h"

InterfazFisica* InterfazFisica::instancia = NULL;

InterfazFisica* InterfazFisica::getInstancia()
{
    if (instancia == NULL)
    {
        instancia = new InterfazFisica();
    }

    return instancia;
}

InterfazFisica::InterfazFisica()
{
    //crearMundo();
}

InterfazFisica::~InterfazFisica()
{
    cout << "BORRANDO INTERFAZ FISICA" << endl;
    instancia = NULL;

    if (detectorColisiones != NULL)
    {
        delete detectorColisiones;
    }
    detectorColisiones = NULL;

    if (mundo != NULL)
    {
        delete mundo;
    }
    mundo = NULL;
}

b2World* InterfazFisica::getMundo() const
{
    return mundo;
}

void InterfazFisica::crearMundo()
{
    cout << "CREO MUNDO FISICO" << endl;
    /*
    b2AABB* worldAABB = new b2AABB();
    worldAABB->lowerBound.Set(20, 20);
    worldAABB->upperBound.Set(750, 550);
    */

    b2Vec2 gravedad(0.0f, -10.0f);
    bool sleep = true;
    mundo = new b2World(gravedad, sleep);
    detectorColisiones = new DetectorColisiones();
    mundo->SetContactListener(detectorColisiones);

    setStep(1.0f/60.0f);
    setIterVel(6);
    setIterPos(6);
}

void InterfazFisica::actualizar()
{
    //cout << "ACTU FISICA" << endl;
    // El volumen influye directamente en la gravedad
    b2Vec2 v(0.0f, -40.0f * InterfazAudio::getInstancia()->getDatosCancion()->getVolumen());
    mundo->SetGravity(v);
    mundo->Step(step, iterVel, iterPos);
    mundo->ClearForces();
}

void InterfazFisica::setStep(float32 s)
{
    step = s;
}

void InterfazFisica::setIterVel(int32 iter)
{
    iterVel = iter;
}

void InterfazFisica::setIterPos(int32 iter)
{
    iterPos = iter;
}

b2Body* InterfazFisica::crearBox(int tipo, Objeto* obj, float32 ancho, float32 alto, float32 densidad, float32 friccion, bool puedeDormir, bool rotacionFija)
{
    b2BodyDef bodyDef;
 
    bodyDef.position.Set(ConversorFisico::getMetersFromPixels(obj->getX()), -1*ConversorFisico::getMetersFromPixels(obj->getY()));
    bodyDef.allowSleep = puedeDormir;
    bodyDef.fixedRotation = rotacionFija;
    bodyDef.userData = obj;

    switch (tipo)
    {
        case ESTATICO:
            bodyDef.type = b2_staticBody;
            break;

        case CINEMATICO:
            bodyDef.type = b2_kinematicBody;
            break;

        case DINAMICO:
            bodyDef.type = b2_dynamicBody;
            break;
    }

    b2Body* body = mundo->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(ancho/2.0f, alto/2.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = densidad;
    fixtureDef.friction = friccion;
    body->CreateFixture(&fixtureDef);

    return body;
}

b2Body* InterfazFisica::crearCirculo(int tipo, Objeto* obj, float32 radio, float32 densidad, float32 friccion, bool puedeDormir)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(ConversorFisico::getMetersFromPixels(obj->getX()), -1*ConversorFisico::getMetersFromPixels(obj->getY()));
    bodyDef.allowSleep = puedeDormir;
    bodyDef.fixedRotation = false;
    bodyDef.userData = obj;

    switch (tipo)
    {
        case ESTATICO:
            bodyDef.type = b2_staticBody;
            break;

        case CINEMATICO:
            bodyDef.type = b2_kinematicBody;
            break;

        case DINAMICO:
            bodyDef.type = b2_dynamicBody;
            break;
    }

    b2Body* body = mundo->CreateBody(&bodyDef);
    b2CircleShape circle;
    circle.m_radius = radio;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = densidad;
    fixtureDef.friction = friccion;
    fixtureDef.restitution = 0.7f;
    body->CreateFixture(&fixtureDef);

    return body;
}