#ifndef PLATAFORMA_MOVIL_H
#define PLATAFORMA_MOVIL_H

#include "ObjetoMovil.h"

// Direcciones para las plataformas
#define IZQUIERDA_DERECHA 1
#define ARRIBA_ABAJO 2
// Direcciones del movimiento
#define IZQUIERDA 1
#define DERECHA 2
#define ARRIBA 3
#define ABAJO 4
// Velocidades para la plataforma
#define PMV0 0
#define PMV1 2
#define PMV2 4
#define PMV3 8

class PlataformaMovil : public ObjetoMovil
{
    public:
        PlataformaMovil(int dir, string nombre, float32 x, float32 y);
        ~PlataformaMovil();
        void pintar() const;
        virtual void actualizar();
        int getDireccion() const;
        void setDireccion(int dir);

    private:
        int direccion;
        int dirMov;
        float xInicial, yInicial;
        Animacion* animacionMov;
        void inicializarAnimaciones();
        void actualizarMovimiento();
        void actualizarVelocidad();
        static int rangoMovimiento;
};

#endif