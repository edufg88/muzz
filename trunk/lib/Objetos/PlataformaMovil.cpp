#include "Objetos/PlataformaMovil.h"
#include "InterfazFisica.h"
#include "ConversorFisico.h"
#include "InterfazAudio.h"
#include "DatosCancion.h"
#include "ProcesadorAudio.h"

int PlataformaMovil::rangoMovimiento = 100;

PlataformaMovil::PlataformaMovil(int dir, string nombre, float32 x, float32 y) : ObjetoMovil(nombre, x, y)
{
    xInicial = x;
    yInicial = y;
    velocidad = PMV2;
    direccion = dir;
    if (dir == ARRIBA_ABAJO) dirMov = ARRIBA;
    if (dir == IZQUIERDA_DERECHA) dirMov = IZQUIERDA;
    animacionMov = new Animacion();
    inicializarAnimaciones();

    ancho = animacionMov->getImagen(0)->width();
    alto = animacionMov->getImagen(0)->height();
    float anchof = ConversorFisico::getMetersFromPixels(ancho);
    float altof = ConversorFisico::getMetersFromPixels(alto);
    setFisica(InterfazFisica::getInstancia()->crearBox(CINEMATICO, this, anchof, altof, 1.0f, 1.0f));
}

PlataformaMovil::~PlataformaMovil()
{
    if (animacionMov != NULL)
    {
        delete animacionMov;
    }
    animacionMov = NULL;
}

void PlataformaMovil::pintar() const
{
    if (visible)
    {
        float32 angulo = InterfazAudio::getInstancia()->getDatosCancion()->getPan()*M_PI/4;
        this->getFisica()->SetTransform(getFisica()->GetPosition(), -angulo);
        angulo = angulo * 180 / M_PI;

        animacionMov->getImagen()->drawRot(posX, posY, ZPERSONAJE, angulo);
    }
}

void PlataformaMovil::actualizar()
{
    ObjetoMovil::actualizar();
    actualizarMovimiento();
    actualizarVelocidad();
}

void PlataformaMovil::actualizarVelocidad()
{
    InterfazAudio* a = InterfazAudio::getInstancia();

    int media = a->getMediaBeats(BASSBEAT) + a->getMediaBeats(MIDBEAT) + a->getMediaBeats(HIGHBEAT);
    int beats = a->getNumeroDeBeats(BASSBEAT) + a->getNumeroDeBeats(MIDBEAT) + a->getNumeroDeBeats(HIGHBEAT);

    // cout << "Media: " << media << ", Beats: " << beats << endl;

    if (beats == 0)
    {
        velocidad = PMV0;
    }
    else if (beats > media*1.5)
    {
        velocidad = PMV3;
    }
    else if (beats < media/2)
    {
        velocidad = PMV1;
    }
    else
    {
        velocidad = PMV2;
    }
}

void PlataformaMovil::actualizarMovimiento()
{
    if (direccion == ARRIBA_ABAJO)
    {
        if (dirMov == ARRIBA)
        {
            if ((yInicial - posY) > rangoMovimiento)
            {
                dirMov = ABAJO;
                b2Vec2 v(0.0f, -1*velocidad);
                fisica->SetLinearVelocity(v);
            }
            else
            {
                if (fisica->GetLinearVelocity().y == 0)
                {
                    b2Vec2 v (0.0f, 1*velocidad);
                    fisica->SetLinearVelocity(v);
                }
            }
        }
        else if (dirMov == ABAJO)
        {
            if ((posY - yInicial) > rangoMovimiento)
            {
                dirMov = ARRIBA;
                b2Vec2 v(0.0f, 1*velocidad);
                fisica->SetLinearVelocity(v);
            }
            else
            {
                if (fisica->GetLinearVelocity().y == 0)
                {
                    b2Vec2 v (0.0f, -1*velocidad);
                    fisica->SetLinearVelocity(v);
                }
            }
        }
    }
    else if (direccion == IZQUIERDA_DERECHA)
    {
        if (dirMov == IZQUIERDA)
        {
            if ((xInicial - posX) > rangoMovimiento)
            {
                dirMov = DERECHA;
                b2Vec2 v(1*velocidad, 0.0f);
                fisica->SetLinearVelocity(v);
            }
            else
            {
                if (fisica->GetLinearVelocity().x == 0)
                {
                    b2Vec2 v (-1*velocidad, 0.0f);
                    fisica->SetLinearVelocity(v);
                }
            }
        }
        else if (dirMov == DERECHA)
        {
            if ((posX - xInicial) > rangoMovimiento)
            {
                dirMov = IZQUIERDA;
                b2Vec2 v(-1*velocidad, 0.0f);
                fisica->SetLinearVelocity(v);
            }
            else
            {
                if (fisica->GetLinearVelocity().x == 0)
                {
                    b2Vec2 v (1*velocidad, 0.0f);
                    fisica->SetLinearVelocity(v);
                }
            }
        }
    }
}

int PlataformaMovil::getDireccion() const
{
    return direccion;
}

void PlataformaMovil::setDireccion(int dir)
{
    direccion = dir;
}

void PlataformaMovil::inicializarAnimaciones()
{
    wstring ruta = rutaSprite();
    ruta += L"plataformamovil.png";
    animacionMov->anyadirImagen(ruta);
}
