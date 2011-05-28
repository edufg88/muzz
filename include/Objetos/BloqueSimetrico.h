#ifndef BLOQUE_SIMETRICO_H
#define BLOQUE_SIMETRICO_H

#include "ObjetoMovil.h"

// Direcciones para los bloques
#define PARADO 0
#define IZQUIERDA 1
#define DERECHA 2
#define ARRIBA 3
#define ABAJO 4

// Velocidades
#define BSV0 0
#define BSV1 2
#define BSV2 4
#define BSV3 8

class BloqueSimetrico : public ObjetoMovil
{
    public:
        BloqueSimetrico(int dir, string nombre, float32 x, float32 y);
        ~BloqueSimetrico();
        void pintar() const;
        virtual void actualizar();
        int getDireccion() const;
        void setDireccion(int dir);
        void cambiarDireccion();
        void parar();
        void setSimetrico(BloqueSimetrico* sim);
        void abrir();
        void cerrar();

    private:
        float xInicial, yInicial;
        int direccion;
        Animacion* animacionMov;
        void inicializarAnimaciones();
        BloqueSimetrico* simetrico;
        void actualizarMovimiento();
        void actualizarVelocidad();
        static int rangoMovimiento;

};

#endif