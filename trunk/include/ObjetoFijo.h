#ifndef OBJETO_FIJO_H
#define OBJETO_FIJO_H

#include "Objeto.h"
#include "Animacion.h"
using namespace std;

class ObjetoFijo : public Objeto
{
    public:
        ObjetoFijo(string nombre, float32 x, float32 y);
        virtual ~ObjetoFijo();
        virtual void pintar() const;

        void setPos(float32 x, float32 y);
        void setAnimacion(Animacion* a);
        Animacion* getAnimacion() const;

    protected:
        Animacion* animacion;
};

#endif