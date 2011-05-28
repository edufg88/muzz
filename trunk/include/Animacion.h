#ifndef ANIMACION_H
#define ANIMACION_H

#include <vector>
#include "GosuAux.h"
using namespace std;

class Animacion
{
    public:
        Animacion();
        ~Animacion();
        // Añade una imágen pasada una ruta
        void anyadirImagen(wstring i);
        // Devulve el número de imágenes de la animación
        int tamanyo();
        // Devuelve la imagen a pintar
        boost::shared_ptr<Gosu::Image> getImagen();
        // Devuelve una imagen en función de su índice
        boost::shared_ptr<Gosu::Image> getImagen(int indice) const;
        // Cambia a la imagen siguiente y la devuelve
        boost::shared_ptr<Gosu::Image> proximaImagen();
        // Cambia a la imagen anterior y la devuelve
        boost::shared_ptr<Gosu::Image> anteriorImagen();
        // Devuelve la imagen actual
        boost::shared_ptr<Gosu::Image> getImagenActual() const;
        // Devuelve el indice de la imagen actual
        int getIndiceImgActual ()  const;
        // Establece como imagen actual la que tiene un indice determinado
        void setIndiceImgActual (int indice);

    private:
        vector<boost::shared_ptr<Gosu::Image> > imagenes;
        int indiceImgActual;
};

#endif