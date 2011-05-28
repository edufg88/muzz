#ifndef ESTRELLA_H
#define ESTRELLA_H

#include "ObjetoFijo.h"

class Estrella : public ObjetoFijo
{
    public:
        Estrella(string nombre, float32 x, float32 y);
        ~Estrella();
        void pintar() const;
        void ejecutar();

    private:
        void inicializarAnimaciones();

};

#endif