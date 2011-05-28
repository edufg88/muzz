#include "Objetos/Bala.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"

int Bala::velocidad = 20;

Bala::Bala(string nombre, float32 x, float32 y) : ObjetoMovil(nombre, x, y)
{
    tipo = BBLANCA;
    visible = true;
    direccion = DERECHA;
    animacionMov = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMov->getImagen(0)->width();
    alto = animacionMov->getImagen(0)->height();
    // Conversión a metros
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    setFisica(InterfazFisica::getInstancia()->crearCirculo(DINAMICO, this, anchof/2, 1.0f, 0.1f, true));
}

Bala::~Bala()
{
    if (animacionMov != NULL)
    {
        delete animacionMov;
    }
    animacionMov = NULL;
}

void Bala::pintar() const
{
    if (visible)
    {
        if (tipo == BBLANCA)
            animacionMov->getImagen(0)->drawRot(posX, posY, ZPERSONAJE, 0);
        else if (tipo == BDORADA)
            animacionMov->getImagen(1)->drawRot(posX, posY, ZPERSONAJE, 0);
    }
}

void Bala::actualizar()
{
    ObjetoMovil::actualizar();
}

void Bala::inicializarAnimaciones()
{
    wstring ruta = Gosu::sharedResourcePrefix() + L"media/objetos/otros/bala/";
    animacionMov->anyadirImagen(ruta + L"bala1.png");
    animacionMov->anyadirImagen(ruta + L"bala2.png");
}

void Bala::setDireccion(int dir)
{
    direccion = dir;

    if (direccion == IZQUIERDA)
    {
        b2Vec2 v(-1.0*velocidad, getFisica()->GetLinearVelocity().y);
        getFisica()->SetLinearVelocity(v);
    }
    else //if (dir == DERECHA)
    {
        b2Vec2 v(+1.0*velocidad, getFisica()->GetLinearVelocity().y);
        getFisica()->SetLinearVelocity(v);
    }
}

int Bala::getDireccion() const
{
    return direccion;
}

int Bala::getTipo() const
{
    return tipo;
}

void Bala::setTipo(int t)
{
    tipo = t;
}

bool Bala::estaFueraDeRango()
{
    if (posY > 650 || posY < 0)
        return true;
    else
        return false;
}