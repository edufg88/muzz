#ifndef ROCA_H
#define ROCA_H

#include "ObjetoMovil.h"

class Roca : public ObjetoMovil
{
    public:
        Roca(string nombre, float32 x, float32 y);
        ~Roca();
        void pintar() const;
        virtual void actualizar();

    private:
        Animacion* animacionMov;
        void inicializarAnimaciones();
};

#endif