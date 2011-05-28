#ifndef CUADRADO_H
#define CUADRADO_H

#include "Enemigo.h"
#include "Animacion.h"
#include "IAEnemigos/IACuadrado.h"

// Velocidades para el cuadrado
#define V0 0
#define V1 2
#define V2 4
#define V3 8

class Cuadrado : public Enemigo
{
    public:
        Cuadrado(string nombre, int x, int y);
        ~Cuadrado();
        void pintar() const;
        void actualizar();
        void moverIzquierda();
        void moverDerecha();
        void parar();

        static int rangoMov;

    private:
        Animacion* animacionMov;
        void inicializarAnimaciones();
        void actualizarMovimiento();
        void actualizarVelocidad();

};

#endif

