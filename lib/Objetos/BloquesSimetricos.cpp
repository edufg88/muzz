#include "Objetos/BloquesSimetricos.h"

BloquesSimetricos::BloquesSimetricos()
{
    b1 = NULL;
    b2 = NULL;
}

BloquesSimetricos::BloquesSimetricos(BloqueSimetrico* a, BloqueSimetrico* b)
{
    b1 = a;
    b2 = b;
}

BloquesSimetricos::~BloquesSimetricos()
{
    if (b1 != NULL)
    {
        delete b1;
    }
    b1 = NULL;
    if (b2 != NULL)
    {
        delete b2;
    }
    b2 = NULL;
}

void BloquesSimetricos::pintar () const
{
    b1->pintar();
    b2->pintar();
}

void BloquesSimetricos::actualizar()
{
    b1->actualizar();
    b2->actualizar();
}

void BloquesSimetricos::setBloques(BloqueSimetrico* a, BloqueSimetrico* b)
{
    b1 = a;
    b2 = b;
}
