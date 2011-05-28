#ifndef CAMARA_H
#define CAMARA_H

#include "Objeto.h"

class Camara
{
    public:
        Camara(int x, int y);
        ~Camara();
        // Enlaza la cámara a un objeto a seguir (normalmente el protagonista)
        bool enlazarCamara(Objeto* o);
        void actualizar();
        void setPos(int x, int y);
        void setLimites(int x, int y);
        int getX() const;
        int getY() const;

    private:
        Objeto* objeto;
        int posX;
        int posY;
        int limiteX;
        int limiteY;
};

#endif