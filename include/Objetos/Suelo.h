#ifndef SUELO_H
#define SUELO_H

#include "ObjetoFijo.h"

// Tamaños de suelos
#define TAM_S 1
#define TAM_M 2
#define TAM_L 3
#define TAM_XL 4

class Suelo : public ObjetoFijo
{
    public:
        Suelo(int tamanyo, string nombre, float32 x, float32 y);
        ~Suelo();
        void pintar() const;
        int getTam () const;
        void setTam (int t);

    private:
        int tam;
        void inicializarAnimaciones();
};


#endif