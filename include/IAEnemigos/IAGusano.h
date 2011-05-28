#ifndef IAGUSANO_H
#define IAGUSANO_H
#include "IAEnemigo.h"

// Estados del gusano
#define PARADO 0
#define MOVIZQUIERDA 1
#define MOVDERECHA 2

class IAGusano : public IAEnemigo
{
    public:
        IAGusano();
        IAGusano(int actitud);
        ~IAGusano();
        void actualizar();
        void actualizarPosProta();
        bool moverDerecha(int dirGusano, int xGusano, int yGusano) const;
        bool moverIzquierda(int dirGusano, int xGusano, int yGusano) const;
        bool parar(int dirGusano, int xGusano, int yGusano) const;
        void setAltoGusano(float alto);

    private:
        float xProta;
        float yProta;
        float altoGusano;
};

#endif