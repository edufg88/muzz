#ifndef IARUEDA_H
#define IARUEDA_H
#include "IAEnemigo.h"

// Estados de la rueda
#define PARADO 0
#define MOVIZQUIERDA 1
#define MOVDERECHA 2

class IARueda : public IAEnemigo
{
    public:
        IARueda();
        IARueda(int actitud);
        ~IARueda();
        void actualizar();
        void actualizarPosProta();
        void setPosSuelo(float x, float y);
        void setAnchoSuelo(int ancho);
        // Consultas a la IA a modo de preguntas
        bool cambiarDireccion(int dirRueda, float xRueda, float yRueda) const;
        bool parar(int dirRueda, float xRueda, float yRueda) const;
        bool saltar(int dirRueda, float xRueda, float yRueda) const;
        int iniciarMovimiento(int dirRueda, float xRueda, float yRueda) const;

    private:
        float xProta;
        float yProta;
        float xSuelo;
        float ySuelo;
        int anchoSuelo;
};

#endif

