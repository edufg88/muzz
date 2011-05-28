#ifndef OBJETO_MOVIL_H
#define OBJETO_MOVIL_H

#include "Objeto.h"
#include "Animacion.h"
using namespace std;

class ObjetoMovil : public Objeto
{
    public:
        ObjetoMovil(string nombre, float32 x, float32 y);
        virtual ~ObjetoMovil();

        virtual void pintar() const;
        virtual void actualizar();

        void setPos(float32 x, float32 y);       
    protected:
        float velocidad;
};

#endif