#ifndef BLOQUES_SIMETRICOS_H
#define BLOQUES_SIMETRICOS_H
/***

 * NO SE USA

 */
#include "Objetos/BloqueSimetrico.h"

class BloquesSimetricos 
{
    public:
        BloquesSimetricos();
        BloquesSimetricos(BloqueSimetrico* a, BloqueSimetrico* b);
        ~BloquesSimetricos();
        void pintar() const;
        virtual void actualizar();
        void setBloques(BloqueSimetrico* a, BloqueSimetrico* b);

    private:
        BloqueSimetrico* b1;
        BloqueSimetrico* b2;
};

#endif