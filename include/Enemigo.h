#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "ObjetoMovil.h"
#include "ConversorFisico.h"
#include "IAEnemigo.h"

class Enemigo : public ObjetoMovil
{
    public:
        Enemigo(string nombre, int x, int y, int pEstado, int pVida, int pDanyo);
        ~Enemigo();
        int getEstado() const;
        int getVida() const;
        int getDanyo() const;
        void sufrirDanyo(int danyo);
        IAEnemigo* getIA() const;
        virtual void pintar() const;
        virtual void actualizar();

    protected:
        int estado;
        int vida;
        int danyo;
        int xInicial;
        int yInicial;
        IAEnemigo* ia;
        virtual void inicializarAnimaciones() = 0;
        Animacion* animacionVida;
        
};

#endif