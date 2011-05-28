#ifndef IABOLA_H
#define IABOLA_H
#include "IAEnemigo.h"
#include "Box2D/Box2D.h"

#define PARADO 0
#define MOVIZQUIERDA 1
#define MOVDERECHA 2
#define MOVARRIBA 3
#define MOVABAJO 4
#define MOVLIBREIZQ 5
#define MOVLIBREDER 6

class IABola : public IAEnemigo
{
    public:
        IABola();
        IABola(int actitud);
        ~IABola();
        void actualizar();
        // Consultas a la IA
        void nuevaActitud(float xBola, float yBola);
        b2Vec2 nuevaDireccion(float xBola, float yBola); // En principio SOLO para actitud AGRESIVA
        static int rangoVision;
    private:
        void actualizarPosProta();
        float xProta;
        float yProta;
};

#endif