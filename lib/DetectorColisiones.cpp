#include "DetectorColisiones.h"
#include "Protagonista.h"
#include "Enemigo.h"
#include "InterfazFisica.h"
#include "Enemigos/Bola.h"
#include "Enemigos/Cuadrado.h"
#include "Enemigos/Triangulo.h"
#include "Enemigos/Rueda.h"
#include "IAEnemigos/IABola.h"
#include "IAEnemigos/IACuadrado.h"
#include "IAEnemigos/IATriangulo.h"
#include "IAEnemigos/IARueda.h"
#include "Objetos/Estrella.h"
#include "Objetos/Silencio.h"
#include "Objetos/BloqueSimetrico.h"
#include "DatosPartida.h"
#include "Juego.h"
#include "Estados/EstadoFin.h"
#include "Objetos/BloqueSimetrico.h"
//#include "ConversorFisico.h"
#include <math.h>

DetectorColisiones::DetectorColisiones()
{

}

DetectorColisiones::~DetectorColisiones()
{

}

void DetectorColisiones::BeginContact(b2Contact* contact)
{

}

void DetectorColisiones::EndContact(b2Contact* contact)
{
    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    const b2Body* bodyA = contact->GetFixtureA()->GetBody();
    const b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Objeto* objA = static_cast<Objeto*>(bodyA->GetUserData());
    Objeto* objB = static_cast<Objeto*>(bodyB->GetUserData());
    Objeto* aux;

    if (objB->getNombre() == "protagonista")
    {
        aux = objA;
        objA = objB;
        objB = aux;
    }

    // Comprobamos las colisiones del protagonista con los enemigos
    if (objA->getNombre() == "protagonista")
    {
        dynamic_cast<Protagonista*>(objA)->reiniciarContactos();
    }

}

void DetectorColisiones::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    contact->GetWorldManifold(&worldManifold);

    const b2Body* bodyA = contact->GetFixtureA()->GetBody();
    const b2Body* bodyB = contact->GetFixtureB()->GetBody();
    Objeto* objA = static_cast<Objeto*>(bodyA->GetUserData());
    Objeto* objB = static_cast<Objeto*>(bodyB->GetUserData());

    // Las notas y los silencios no generan colisión con los demás objetos
    if ((objA->getNombre() == "estrella" && esObjeto(objB)) || (esObjeto(objA) && objB->getNombre() == "estrella"))
    {
        contact->SetEnabled(false);
    }
    if ((objA->getNombre() == "silencio" && esObjeto(objB)) || (esObjeto(objA) && objB->getNombre() == "silencio"))
    {
        contact->SetEnabled(false);
    }

    // Los enemigos solo colisionan con el protagonista
    if (((esObjeto(objA) && !esSuperficie(objA)) && esEnemigo(objB)) ||
        (esEnemigo(objA) && (esObjeto(objB) && !esSuperficie(objB))))
    {
        contact->SetEnabled(false);
    }

    b2PointState state1[2], state2[2];
    b2GetPointStates(state1, state2, oldManifold, contact->GetManifold());

    if(state2[0] == b2_addState)
    {
//        const b2Body* bodyA = contact->GetFixtureA()->GetBody();
//        const b2Body* bodyB = contact->GetFixtureB()->GetBody();
//        Objeto* objA = static_cast<Objeto*>(bodyA->GetUserData());
//        Objeto* objB = static_cast<Objeto*>(bodyB->GetUserData());
        
        Objeto* aux;

        if (objB->getNombre() == "protagonista")
        {
            aux = objA;
            objA = objB;
            objB = aux;
        }

        // Comprobamos las colisiones del protagonista con los enemigos
        if (objA->getNombre() == "protagonista")
        {
            if (esEnemigo(objB))
            {
                colProtagonistaEnemigo(objA, objB);
            }

            else if (esObjeto(objB))
            {
                colProtagonistaObjeto(objA, objB, worldManifold.normal);
            }
        }
        else
        {
            // Comprobamos las colisiones de la bala
            if (objB->getNombre() == "bala")
            {
                aux = objA;
                objA = objB;
                objB = aux;
            }
            if (objA->getNombre() == "bala")
            {
                if (esEnemigo(objB))
                {
                    colBalaEnemigo(objA, objB);
                }
                else if (esObjeto(objB))
                {
                    colBalaObjeto(objA, objB);
                }
            }

            // Comprobamos si es un enemigo
            if (esEnemigo(objB))
            {
                aux = objA;
                objA = objB;
                objB = aux;
            }
            if (esEnemigo(objA))
            {
                if (esSuperficie(objB))
                {
                    colEnemigoSuelo(objA, objB);
                }
            }

            if (objA->getNombre() == "bloquesimetrico" && objB->getNombre() == "bloquesimetrico")
            {
                colBloqueBloque(objA, objB);
            }
        }

        b2Vec2 point = worldManifold.points[0];
        b2Vec2 vA = bodyA->GetLinearVelocityFromWorldPoint(point);
        b2Vec2 vB = bodyB->GetLinearVelocityFromWorldPoint(point);
        
        float32 approachVelocity = b2Dot(vB-vA, worldManifold.normal);

        if (fabs(approachVelocity) > 1.0f)
        {
            //cout << "Colision" << endl;
        }
    }
}

void DetectorColisiones::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}

void DetectorColisiones::colProtagonistaEnemigo(Objeto* prota, Objeto* enemigo)
{
    Protagonista* p = dynamic_cast<Protagonista*>(prota);
    p->sufrirDanyo(dynamic_cast<Enemigo*>(enemigo)->getDanyo());

    // Controlamos la dirección del impacto
    // Si el prota está a la izquierda
    if (prota->getX() < enemigo->getX())
    {
        p->chocar(IZQUIERDA);
    }
    else
    {
        p->chocar(DERECHA);
    }
}

void DetectorColisiones::colProtagonistaObjeto(Objeto* prota, Objeto* objeto, b2Vec2 normal)
{
    Protagonista* protagonista = dynamic_cast<Protagonista*>(prota);

    // Según el ángulo de la normal establecemos que tipo de contacto tiene el personaje
    if (normal.x >= 0.8 && normal.y > -0.6 && normal.y < 0.6)
    {
        protagonista->setContraParedDer(true);
    }
    else if (normal.x <= -0.8 && normal.y > -0.6 && normal.y < 0.6)
    {
        protagonista->setContraParedIzq(true);

        if (objeto->getNombre() == "bloquesimetrico" && protagonista->esContraParedDer())
        {
            protagonista->sufrirDanyo(40);
        }
    }
    else if (normal.y > 0.8 && normal.x > -0.6 && normal.x < 0.6)
    {
        protagonista->setContraParedArriba(true);

        // Si lo que está encima es un pico o una roca, nos hace daño
        if (objeto->getNombre() == "pico" || objeto->getNombre() == "roca")
        {
            protagonista->sufrirDanyo(40);
        }
        if (objeto->getNombre() == "bloquesimetrico" && protagonista->esContraParedAbajo())
        {
            protagonista->sufrirDanyo(40);
        }
    }
    else if (normal.y < 0.8 && normal.x > -0.6 && normal.x < 0.6)
    {
        protagonista->setContraParedAbajo(true);
        protagonista->setPuedeSaltar(true);
        protagonista->recuperar();
    }

    // Comprobamos si es un objeto de bonificación
    if (objeto->getNombre() == "silencio")
    {
        Silencio* s = dynamic_cast<Silencio*>(objeto);
        s->ejecutar();
        objeto->setActivo(false);
        objeto->getFisica()->SetActive(false);
    }
    else if (objeto->getNombre() == "estrella")
    {
        Estrella* e = dynamic_cast<Estrella*>(objeto);
        e->ejecutar();
        objeto->setActivo(false);
        objeto->getFisica()->SetActive(false);
    }
    else if (objeto->getNombre() == "meta")
    {
        Juego::getInstancia()->setFinalizado();
    }
    else if (objeto->getNombre() == "pinchos")
    {
        if (normal.y < 0.8 && normal.x > -0.6 && normal.x < 0.6)
        {
            if (protagonista->getDireccion() == IZQUIERDA)
            {
                cout << protagonista->getFisica()->GetLinearVelocity().x << ", " << protagonista->getFisica()->GetLinearVelocity().y << endl;
                protagonista->chocar(DERECHA);
                b2Vec2 v(0.0f, 0.0f);
                protagonista->getFisica()->SetLinearVelocity(v);
                protagonista->getFisica()->ApplyAngularImpulse(32);
                cout << protagonista->getFisica()->GetLinearVelocity().x << ", " << protagonista->getFisica()->GetLinearVelocity().y << endl;
            }
            else if (protagonista->getDireccion() == DERECHA)
                protagonista->chocar(IZQUIERDA);
        }
    }
    else if (objeto->getNombre() == "bloquesimetrico")
    {

    }

    //cout << "obj: " << objeto->getNombre() << " " << normal.x << ", " << normal.y << endl;
}

void DetectorColisiones::colBalaEnemigo(Objeto* bala, Objeto* enemigo)
{
    Bala* b = dynamic_cast<Bala*>(bala);
    
    // Al colisionar la bala, eliminamos la bala y aplicamos daño al enemigo
    bala->setActivo(false);

    cout << "TIPO  " << b->getTipo() << endl;
    // En función del enemigo las balas harán más daño o menos
    if (enemigo->getNombre() == "bola")
    {
        if (b->getTipo() == BBLANCA)
            dynamic_cast<Enemigo*>(enemigo)->sufrirDanyo(40);
        else if (b->getTipo() == BDORADA)
            dynamic_cast<Enemigo*>(enemigo)->sufrirDanyo(50);
    }
    else if (enemigo->getNombre() == "rueda")
    {
        if (b->getTipo() == BBLANCA)
            dynamic_cast<Enemigo*>(enemigo)->sufrirDanyo(30);
        else if (b->getTipo() == BDORADA)
            dynamic_cast<Enemigo*>(enemigo)->sufrirDanyo(40);
    }
    else if (enemigo->getNombre() == "cuadrado")
    {
        if (b->getTipo() == BBLANCA)
            dynamic_cast<Enemigo*>(enemigo)->sufrirDanyo(20);
        else if (b->getTipo() == BDORADA)
            dynamic_cast<Enemigo*>(enemigo)->sufrirDanyo(30);
    }
    else if (enemigo->getNombre() == "triangulo")
    {
        if (b->getTipo() == BBLANCA)
            dynamic_cast<Enemigo*>(enemigo)->sufrirDanyo(10);
        else if (b->getTipo() == BDORADA)
            dynamic_cast<Enemigo*>(enemigo)->sufrirDanyo(20);
    }
}

void DetectorColisiones::colBalaObjeto(Objeto* bala, Objeto* objeto)
{
    // Al colisionar la bala, eliminamos la bala
    bala->setActivo(false);
}

void DetectorColisiones::colEnemigoSuelo(Objeto* enemigo, Objeto* superficie)
{
    if (enemigo->getNombre() == "bola")
    {

    }
    else if (enemigo->getNombre() == "cuadrado")
    {
        Cuadrado* c = dynamic_cast<Cuadrado*>(enemigo);
        IACuadrado* iac = dynamic_cast<IACuadrado*>(c->getIA());
        // Establecemos la posicion del suelo donde está el enemigo
        iac->setPosSuelo(superficie->getX(), superficie->getY());
        // Establecemos el ancho del suelo
        iac->setAnchoSuelo(superficie->getAncho());
    }
    else if (enemigo->getNombre() == "triangulo")
    {
        
    }
    else if (enemigo->getNombre() == "rueda")
    {
        Rueda* r = dynamic_cast<Rueda*>(enemigo);
        IARueda* iar = dynamic_cast<IARueda*>(r->getIA());
        // Establecemos la posicion del suelo donde está el enemigo
        iar->setPosSuelo(superficie->getX(), superficie->getY());
        // Establecemos el ancho del suelo
        iar->setAnchoSuelo(superficie->getAncho());
    }
}

void colObjetoObjeto(Objeto* obj1, Objeto* obj2)
{

}

void DetectorColisiones::colBloqueBloque(Objeto* b1, Objeto* b2)
{
    cout << "Col bloque bloque" << endl;
    BloqueSimetrico* bloque1 = dynamic_cast<BloqueSimetrico*>(b1);
    BloqueSimetrico* bloque2 = dynamic_cast<BloqueSimetrico*>(b2);

    bloque1->cambiarDireccion();
    bloque2->cambiarDireccion();
}

bool DetectorColisiones::esEnemigo(Objeto* obj) const
{
    return (obj->getNombre() == "bola" ||obj->getNombre() == "cuadrado"
         || obj->getNombre() == "triangulo" || obj->getNombre() == "rueda");
}

bool DetectorColisiones::esObjeto(Objeto* obj) const
{
    return (obj->getNombre() == "suelo" || obj->getNombre() == "roca"
         || obj->getNombre() == "pico" || obj->getNombre() == "pinchos"
         || obj->getNombre() == "plataforma" || obj->getNombre() == "plataformamovil"
         || obj->getNombre() == "estrella" || obj->getNombre() == "silencio"
         || obj->getNombre() == "bloquesimetrico" || obj->getNombre() == "meta" );
}

bool DetectorColisiones::esSuperficie(Objeto* obj) const
{
    return (obj->getNombre() == "suelo" || obj->getNombre() == "plataforma"
            || obj->getNombre() == "plataformamovil");
}