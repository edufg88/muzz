#ifndef BALA_H
#define BALA_H

#include "ObjetoMovil.h"

// Direcciones posibles de la bala (equivalente a las direcciones del personaje)
#define IZQUIERDA 1
#define DERECHA 2 

// Tipos de bala
#define BBLANCA 1
#define BDORADA 2

class Bala : public ObjetoMovil
{
    public:
        Bala(string nombre, float32 x, float32 y);
        ~Bala();
        void pintar() const;
        virtual void actualizar();
        void setDireccion (int dir);
        int getDireccion () const;
        int getTipo() const;
        void setTipo(int tipo);
        bool estaFueraDeRango();

    private:
        static int velocidad;
        int direccion;
        Animacion* animacionMov;
        void inicializarAnimaciones();
        int tipo;
        
};

#endif