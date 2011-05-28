#ifndef PINCHOS_H
#define PINCHOS_H

#include "ObjetoMovil.h"

class Pinchos : public ObjetoMovil
{
    public:
        Pinchos(int numero, string nombre, float32 x, float32 y);
        ~Pinchos();
        void pintar() const;
        virtual void actualizar();

    private:
        int numero;
        Animacion* animacionMov;
        void inicializarAnimaciones();
};

#endif