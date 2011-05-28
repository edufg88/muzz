#ifndef BOLA_H
#define BOLA_H

#include "Enemigo.h"
#include "Box2D/Box2D.h"

// Velocidades de la bola
#define VB0 0
#define VB1 1
#define VB2 3
#define VB3 5

class Bola : public Enemigo
{
    public:
        Bola(string nombre, int x, int y);
        ~Bola();
        void pintar() const;
        void actualizar();

        void moverIzquierda();
        void moverDerecha();
        void moverArriba();
        void moverAbajo();
        void moverDireccion();
        void parar();

        static int rangoMov;

    private:
        Animacion* animacionMI;
        Animacion* animacionMD;
        void inicializarAnimaciones();
        void actualizarMovimiento();
        void actualizarVelocidad();
        b2Vec2 direccion;
};

#endif