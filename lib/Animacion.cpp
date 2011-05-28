#include "Animacion.h"
#include "Juego.h"

Animacion::Animacion()
{
    indiceImgActual = 0;
}

Animacion::~Animacion()
{

}

void Animacion::anyadirImagen(wstring i)
{
    boost::shared_ptr<Gosu::Image> imagen;
    imagen.reset(new Gosu::Image(Juego::getInstancia()->graphics(), i));
    imagenes.push_back(imagen);
}

int Animacion::tamanyo()
{
    return imagenes.size();
}

boost::shared_ptr<Gosu::Image> Animacion::getImagen() 
{
    indiceImgActual = Gosu::milliseconds() / 100 % imagenes.size();
    return imagenes.at(indiceImgActual);
}

boost::shared_ptr<Gosu::Image> Animacion::getImagen(int indice) const
{
    return imagenes.at(indice);
}

boost::shared_ptr<Gosu::Image> Animacion::proximaImagen()
{
    indiceImgActual++;

    if (indiceImgActual == imagenes.size())
    {
        indiceImgActual--;
    }

    return imagenes.at(indiceImgActual);
}

boost::shared_ptr<Gosu::Image> Animacion::anteriorImagen()
{
     indiceImgActual--;
     return imagenes.at(indiceImgActual);
}

boost::shared_ptr<Gosu::Image> Animacion::getImagenActual() const
{
     return imagenes.at(indiceImgActual);
}

int Animacion::getIndiceImgActual ()  const
{
     return indiceImgActual;
}

void Animacion::setIndiceImgActual (int indice)
{
    indiceImgActual = indice;

    if (indice < 0)
            indice = 0;
    else if (indice >= imagenes.size())
            indice = imagenes.size()-1;
}