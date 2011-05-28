#ifndef RUEDA_H
#define RUEDA_H

#include "Enemigo.h"

// Velocidades de la rueda
#define VR0 0
#define VR1 1000
#define VR2 2000
#define VR3 3000

class Rueda : public Enemigo
{
    public:
        Rueda(string nombre, int x, int y);
        ~Rueda();
        void pintar() const;
        void actualizar();

        void moverIzquierda();
        void moverDerecha();
        void parar();
        void saltar();

    private:
        Animacion* animacionMov;
        void inicializarAnimaciones();
        void actualizarMovimiento();
        void actualizarVelocidad();
        int rangoMov;
};

#endif