#ifndef GUSANO_H
#define GUSANO_H

#include "Enemigo.h"

class Gusano : public Enemigo
{
public:
    Gusano (string nombre, int x, int y);
    ~Gusano ();
    void pintar() const;
    void actualizar();

    void moverIzquierda();
    void moverDerecha();
    void parar();

private:
    Animacion* animacionMov;
    void inicializarAnimaciones();
    void actualizarMovimiento();
    long timerMovimiento;

};


#endif