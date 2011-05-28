#ifndef IATRIANGULO_H
#define IATRIANGULO_H
#include "IAEnemigo.h"
#include "Box2D/Box2D.h"
// Estados del triangulo
#define PARADO 0
#define MOVIZQUIERDA 1
#define MOVDERECHA 2
#define MOVARRIBA 3
#define MOVABAJO 4
#define MOVLIBREIZQ 5
#define MOVLIBREDER 6

class IATriangulo : public IAEnemigo
{
    public:
        IATriangulo();
        IATriangulo(int actitud);
        ~IATriangulo();
        void actualizar();
        void actualizarPosProta();

        bool atacar(int xTriangulo, int yTriangulo) const;
        bool escapar(int xTriangulo, int yTriangulo) const;
        //bool volver();
        //bool parar();

        bool moverDerecha(int dirTriangulo, int xTriangulo, int yTriangulo) const;
        bool moverIzquierda(int dirTriangulo, int xTriangulo, int yTriangulo) const;
        bool parar(int dirTriangulo, int xTriangulo, int yTriangulo) const;
//        void nuevaActitud(float xBola, float yBola);
        b2Vec2 nuevaDireccion(float xTriangulo, float yTriangulo);
//        int nuevoEstado(int dirProta, float xBola, float yBola); 

    private:
        float xProta;
        float yProta;
};

#endif