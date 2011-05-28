#ifndef OBJETO_H
#define OBJETO_H

#include "GosuAux.h"
#include <Box2D/Box2D.h>
using namespace std;

class  Objeto
{
    public:
        Objeto(string nombre, float32 x, float32 y);
        virtual ~Objeto() = 0;
        virtual void setPos(float32 x, float32 y) = 0;
        float32 getX() const;
        float32 getY() const;
        float32 getAncho() const;
        float32 getAlto() const;
        void setAncho(float32 pAncho);
        void setAlto(float32 pAlto);
        b2Body* getFisica() const;
        bool esVisible() const;
        void setVisible(bool vis);
        bool esActivo() const;
        void setActivo(bool act);
        void setFisica(b2Body* f);
        string getNombre() const;
        void setNombre(string pNombre);
        virtual void pintar() const = 0;
        virtual void actualizar();

    protected:
        string nombre;
        float32 posX;
        float32 posY;
        float32 ancho;
        float32 alto;

        bool visible;
        bool activo;
        b2Body* fisica; // Enlace con el objeto físico

        // Como cada objeto tendra un sprite u otro en funcion del género
        // este método devuelve la ruta especifica donde encontrar el sprite
        wstring rutaSprite();
};

#endif