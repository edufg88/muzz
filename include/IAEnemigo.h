#ifndef IAENEMIGO_H
#define IAENEMIGO_H

#include "InterfazIA.h"
// Comportamientos
#define AGRESIVO 1
#define PASIVO 2
#define EVASIVO 3

class IAEnemigo
{
    public:
        IAEnemigo();
        IAEnemigo(int pActitud);
        ~IAEnemigo();
        int getActitud() const;
        void setActitud(int act);
        virtual void actualizar() = 0;

    protected:
        int actitud;
};

#endif