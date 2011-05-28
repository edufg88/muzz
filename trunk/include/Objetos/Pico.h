#ifndef PICO_H
#define PICO_H

#include "ObjetoMovil.h"

class Pico : public ObjetoMovil
{
    public:
        Pico(string nombre, float32 x, float32 y);
        ~Pico();
        void pintar() const;
        virtual void actualizar();

    private:
        Animacion* animacionMov;
        void inicializarAnimaciones();
};

#endif