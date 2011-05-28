#ifndef IACUADRADO_H
#define IACUADRADO_H
#include "IAEnemigo.h"

#ifndef PARADO
    #define PARADO 0
#endif
#ifndef MOVIZQUIERDA
    #define MOVIZQUIERDA 1
#endif
#ifndef MOVDERECHA
    #define MOVDERECHA 2
#endif

class IACuadrado : public IAEnemigo
{
    public:
        IACuadrado();
        IACuadrado(int actitud);
        ~IACuadrado();
        void actualizar();
        void actualizarPosProta();
        void setPosSuelo(float x, float y);
        void setAnchoSuelo(int ancho);
        // Consultas a la IA a modo de preguntas
        bool cambiarDireccion(int dirCuadrado, float xCuadrado, float yCuadrado) const;
        bool parar(int dirCuadrado,float xCuadrado, float yCuadrado) const;
        int iniciarMovimiento(int dirCuadrado,float xCuadrado, float yCuadrado) const;
    private:
        /* Posición del protagonista y el suelo donde está el cuadrado
         * Se utilizan para trazar las reglas de movimiento 
         * */
        float xProta;
        float yProta;
        float xSuelo;
        float ySuelo;
        int anchoSuelo;
};

#endif