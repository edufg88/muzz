#ifndef SILENCIO_H
#define SILENCIO_H

#include "ObjetoFijo.h"

// Tipos de silencio
#define BLANCA 0
#define NEGRA 1
#define CORCHEA 2
#define SEMICORCHEA 3

class Silencio : public ObjetoFijo
{
    public:
        Silencio(int tipo, string nombre, float32 x, float32 y);
        ~Silencio();
        void pintar() const;
        int getTipo() const;
        void setTipo(int tipo);
        void ejecutar();
    private:
        void inicializarAnimaciones();
        int tipo;

};

#endif