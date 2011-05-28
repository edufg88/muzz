#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "ObjetoFijo.h"

class Plataforma : public ObjetoFijo
{
    public:
        Plataforma(string nombre, float32 x, float32 y);
        ~Plataforma();
        void pintar() const;
        
    private:
        void inicializarAnimaciones();

};

#endif