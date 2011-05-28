#ifndef META_H
#define META_H

#include "ObjetoFijo.h"

class Meta : public ObjetoFijo
{
    public:
        Meta(string nombre, float32 x, float32 y);
        ~Meta();
        void pintar() const;
        void ejecutar();

    private:
        void inicializarAnimaciones();

};

#endif