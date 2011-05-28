#ifndef DETECTOR_COLISIONES_H
#define DETECTOR_COLISIONES_H
#include <iostream>
#include <Box2D/Box2D.h>
#include "Objeto.h"
using namespace std;

class DetectorColisiones : public b2ContactListener
{
    public:
        DetectorColisiones();
        ~DetectorColisiones();
        // Cuando aparece el primer contacto entre 2 objetos
        void BeginContact(b2Contact* contact);
        // Cuando desaparece el contacto entre 2 objetos
        void EndContact(b2Contact* contact);
        // Después de la detección de colisiones pero antes de su resolución
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        //
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

        // Para resolver colisiones particulares
        void colProtagonistaEnemigo(Objeto* prota, Objeto* enemigo);
        void colProtagonistaObjeto(Objeto* prota, Objeto* objeto, b2Vec2 normal);
        void colBalaEnemigo(Objeto* bala, Objeto* enemigo);
        void colBalaObjeto(Objeto* bala, Objeto* objeto);
        void colEnemigoSuelo(Objeto* enemigo, Objeto* superficie);
        void colObjetoObjeto(Objeto* obj1, Objeto* obj2);
        void colBloqueBloque(Objeto* b1, Objeto* b2);
    private:
        bool esEnemigo(Objeto* obj) const;
        bool esObjeto(Objeto* obj) const;
        bool esSuperficie(Objeto* obj) const;
        b2WorldManifold worldManifold;
};

#endif