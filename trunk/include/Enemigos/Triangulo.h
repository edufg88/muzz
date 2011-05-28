#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Enemigo.h"

// Define los estados particulares del triángulo
#define PARADO 0
#define BASE 1
#define ATACANDO 2
#define ESCAPANDO 3
#define VOLVIENDO 4

class Triangulo : public Enemigo
{
    public:
        Triangulo (string nombre, int x, int y);
        ~Triangulo ();
        void pintar() const;
        void actualizar();

        // Borrar!!
        void moverIzquierda();
        void moverDerecha();
        void moverDireccion();
        
        void atacar();
        void escapar();
        void volver();
        void parar();

        Animacion* getAnimacionMI() const { return animacionMI; }
        Animacion* getAnimacionMD() const { return animacionMD; }

        static int rangoMov;

    private:
        float xInicial, yInicial;
        float angulo;
        Animacion* animacionMI;
        Animacion* animacionMD;
        Animacion* animacionPivote;
        void inicializarAnimaciones();
        void actualizarMovimiento();
        b2Vec2 direccion;
        int estado2;
        int velocidadVuelta;

};


#endif