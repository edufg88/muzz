#include "Protagonista.h"
#include "Juego.h"
#include "DatosPartida.h"
#include "ConversorFisico.h"
#include "Estados/EstadoGameOver.h"
#include <iostream>
using namespace std;

long Protagonista::potenciaSalto = 100;
int Protagonista::potenciaChoque = 50;

Protagonista::Protagonista(string nombre, float32 x, float32 y) : ObjetoMovil(nombre, x, y)
{
    contraParedDer = contraParedIzq = contraParedAbajo = contraParedArriba = false;
    estado = PARADO; 
    direccion = DERECHA;
    velocidad = 9;
    puedeSaltar = true;
    timerSalto = 0;
    
    animacionParado = new Animacion();
    animacionMI = new Animacion();
    animacionMD = new Animacion();
    animacionSaltarI = new Animacion();
    animacionSaltarD = new Animacion();
    animacionDispararI = new Animacion();
    animacionDispararD = new Animacion();
    animacionDispSaltI = new Animacion();
    animacionDispSaltD = new Animacion();
    animacionChoqueI = new Animacion();
    animacionChoqueD = new Animacion();

    inicializarAnimaciones();

    ancho = getAnimacionParado()->getImagen(0)->width();
    alto = getAnimacionParado()->getImagen(0)->height();
    // Hacemos la conversion para el motor físico de píxels->metros
    float anchof = ConversorFisico::getMetersFromPixels(ancho/2);
    float altof = ConversorFisico::getMetersFromPixels(alto-5);
    setFisica(InterfazFisica::getInstancia()->crearBox(DINAMICO, this, anchof, altof, 0.1f, 5.0f, false, true));
}

Protagonista::~Protagonista()
{
    if (animacionParado != NULL)
        delete animacionParado;
    animacionParado = NULL;
    if (animacionMI != NULL)
        delete animacionMI;
    animacionMI = NULL;
    if (animacionMD != NULL)
        delete animacionMD;
    animacionMD = NULL;
    if (animacionSaltarI != NULL)
        delete animacionSaltarI;
    animacionSaltarI = NULL;
    if (animacionSaltarD != NULL)
        delete animacionSaltarD;
    animacionSaltarD = NULL;
    if (animacionDispararI != NULL)
        delete animacionDispararI;
    animacionDispararI = NULL;
    if (animacionDispararD != NULL)
        delete animacionDispararD;
    animacionDispararD = NULL;
    if (animacionDispSaltI != NULL)
        delete animacionDispSaltI;
    animacionDispSaltI = NULL;
    if (animacionDispSaltD != NULL)
        delete animacionDispSaltD;
    animacionDispSaltD = NULL;
    if (animacionChoqueI != NULL)
        delete animacionChoqueI;
    animacionChoqueI = NULL;
    if (animacionChoqueD != NULL)
        delete animacionChoqueD;
    animacionChoqueD = NULL;

    // Borramos las balas si queda alguna
    vector<Bala*>::iterator it;
    for (it = disparos.begin(); it != disparos.end(); it++)
    {
        Bala* b = *it;
        if (b != NULL)
            delete b;
        b = NULL;
    }
    disparos.clear();
}

void Protagonista::pintar() const
{
    if (visible)
    {
        switch (estado)
        {
            case PARADO:
                animacionParado->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, 0);
                break;
            case MOVIMIENTO:
                if (direccion == IZQUIERDA)
                {
                    animacionMI->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                else if (direccion == DERECHA)
                {
                    animacionMD->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                break;
            case SALTANDO:
                if (direccion == IZQUIERDA)
                {
                    animacionSaltarI->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                else if (direccion == DERECHA)
                {
                    animacionSaltarD->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                break;
            case DISPARANDO_PARADO:
                if (direccion == IZQUIERDA)
                {
                    animacionParado->getImagen(3)->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                else if (direccion == DERECHA)
                {
                    animacionParado->getImagen(2)->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                break;
            case DISPARANDO_MOVIMIENTO:
                if (direccion == IZQUIERDA)
                {
                    animacionDispararI->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                else if (direccion == DERECHA)
                {
                    animacionDispararD->getImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                break;
            case DISPARANDO_SALTANDO:
                if (direccion == IZQUIERDA)
                {
                    animacionDispSaltI->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                else if (direccion == DERECHA)
                {
                    animacionDispSaltD->getImagenActual()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                break;
            case HERIDO:
                if (direccion == IZQUIERDA)
                {
                    animacionChoqueI->proximaImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                else if (direccion == DERECHA)
                {
                    animacionChoqueD->proximaImagen()->drawRot(posX, posY, ZPERSONAJE, 0);
                }
                break;
        }

        // Pintamos también los disparos
        pintarDisparos();
    }
}

void Protagonista::actualizar()
{
    //cout << "Prota( " << posX << ", " << posY  << ") " << endl;
    ObjetoMovil::actualizar();
    actualizarEstado();
    actualizarDisparos();
    actualizarVida();
}

void Protagonista::actualizarVida()
{
    // Comprobamos si GAME OVER

    // Miramos si se ha caído
    if (posY > 600)
    {
        cout << "Muerte por caida" << endl;
        Juego::getInstancia()->cambiarEstado(ESTADO_GAMEOVER);
    }
    // Miramos la energía
    else if (DatosPartida::getInstancia()->getVida() <= 0)
    {
        cout << "Muerte por falta de vida" << endl;
        Juego::getInstancia()->cambiarEstado(ESTADO_GAMEOVER);
    }
}

void Protagonista::actualizarEstado()
{
    if (estado == SALTANDO || estado == DISPARANDO_SALTANDO)
    {
        // Si puede saltar es que ya ha llegado al suelo
        if (puedeSaltar)
        {
            if (estado == DISPARANDO_SALTANDO)
            {
                estado = DISPARANDO_PARADO;

                if (direccion == IZQUIERDA)
                {
                    animacionParado->setIndiceImgActual(3);
                }
                else if (direccion == DERECHA)
                {
                    animacionParado->setIndiceImgActual(2);
                }
            }
            else
            {
                estado = PARADO;
                animacionSaltarI->setIndiceImgActual(0);
                animacionSaltarD->setIndiceImgActual(0);
                animacionDispSaltI->setIndiceImgActual(0);
                animacionDispSaltD->setIndiceImgActual(0);
            }
        }
        // Todavía está en el aire
        else
        {
            if (estado == DISPARANDO_SALTANDO)
            {
                if (direccion == IZQUIERDA)
                {
                    animacionDispSaltI->proximaImagen();
                }
                else if (direccion == DERECHA)
                {
                    animacionDispSaltD->proximaImagen();
                }
            }
            else
            {
                if (direccion == IZQUIERDA)
                {
                    animacionSaltarI->proximaImagen();
                }
                else if (direccion == DERECHA)
                {
                    animacionSaltarD->proximaImagen();
                }

                // Comprobamos que no se haya bloqueado en un salto
                if ((Gosu::milliseconds() - timerSalto) > 4000)
                {
                        puedeSaltar = true;                 
                }
            }
        }
    }
}

void Protagonista::actualizarDisparos()
{
    // Eliminamos las balas inactivas
    vector<Bala*>::iterator it;
    vector<Bala*> v;

    for (it = disparos.begin(); it != disparos.end(); it++)
    {
        Bala* b = *it;

        if (b->esActivo() == false || b->estaFueraDeRango() == true)
        {
            if (b != NULL)
            delete b; b = NULL;
        }
        else
        {
            b->actualizar();
            v.push_back(b);
        }
    }

    disparos = v;

//    vector<Bala*>::iterator it;
//    int i = 0;
//    for (it = disparos.begin(); it != disparos.end(); it++)
//    {
//        cout << "IT: " << (*it)->getNombre() << " " << i << endl;
//        disparos.erase(it);
//        if ((*it)->esActivo() == false)
//        {
//            Bala* b = *it;
//            disparos.erase(it);
//            if (b != NULL)
//            {
//                delete b;
//                b = NULL;
//            }
//        }
//        else
//        {
//            if ((*it) != NULL)
//                (*it)->actualizar();
//        }
//                i++;
    
}

void Protagonista::pintarDisparos() const
{
    for (int i = 0; i < disparos.size(); i++)
    {
        if (disparos[i]->esActivo())
            disparos[i]->pintar();
    }
}

void Protagonista::parar()
{
    if (estado != SALTANDO && estado != DISPARANDO_SALTANDO && estado != HERIDO)
    {
        b2Vec2 v(0.0f, getFisica()->GetLinearVelocity().y);
        getFisica()->SetLinearVelocity(v);
        
        estado = PARADO;
    }
}

void Protagonista::moverIzquierda()
{
    if (!esContraParedIzq() && estado != HERIDO)
    {
        b2Vec2 v(-1.0*velocidad, getFisica()->GetLinearVelocity().y);
        getFisica()->SetLinearVelocity(v);
        direccion = IZQUIERDA;
    }
    
    if (puedeSaltar)
    {
        if (estado == PARADO)
        {
            estado = MOVIMIENTO;
        }
        else if (estado == DISPARANDO_PARADO)
        {
            estado = DISPARANDO_MOVIMIENTO;
        }
    }
}

void Protagonista::moverDerecha()
{
    if (!esContraParedDer() && estado != HERIDO)
    {
        b2Vec2 v(1.0*velocidad, getFisica()->GetLinearVelocity().y);
        getFisica()->SetLinearVelocity(v);
        direccion = DERECHA;
    }

    if (puedeSaltar)
    {
        if (estado == PARADO)
        {
            estado = MOVIMIENTO;
        }
        else if (estado == DISPARANDO_PARADO)
        {
            estado = DISPARANDO_MOVIMIENTO;
        }
    }
    
}

void Protagonista::saltar()
{
    if (puedeSaltar)
    {
        timerSalto = Gosu::milliseconds();

        puedeSaltar = false;
        b2Vec2 fuerza(0.0f, 1.0*potenciaSalto);
        b2Vec2 punto = getFisica()->GetPosition();
        getFisica()->ApplyForce(fuerza, punto);

        if (estado == DISPARANDO_PARADO || estado == DISPARANDO_MOVIMIENTO)
        {
            estado = DISPARANDO_SALTANDO;
        }
        else
        {
            estado = SALTANDO;
        }
    }
}

void Protagonista::disparar(bool especial)
{
    // Creamos una nueva bala
    if (estado != HERIDO)
    {
        Bala* b = NULL;
        if (direccion == IZQUIERDA)
        {
            b = new Bala("bala", this->getX() - ancho, this->getY());
            // Si se ha disparado en un beat, la bala será especial
            if (especial)
                b->setTipo(BDORADA);
        }
        else if (direccion == DERECHA)
        {
            b = new Bala("bala", this->getX() + ancho, this->getY());
            // Si se ha disparado en un beat, la bala será especial
            if (especial)
                b->setTipo(BDORADA);
        }
        b->setDireccion(direccion);
        // La añadimos a la lista de balas que hay en pantalla
        disparos.push_back(b);

        if (estado == MOVIMIENTO)
        {
            estado = DISPARANDO_MOVIMIENTO;
        }
        else if (estado == PARADO)
        {
            estado = DISPARANDO_PARADO;
        }
        else if (estado == SALTANDO)
        {
            estado = DISPARANDO_SALTANDO;
        }
    }
}

void Protagonista::pararDisparar()
{
    if (estado == DISPARANDO_MOVIMIENTO)
    {
        estado = MOVIMIENTO;
    }
    else if (estado == DISPARANDO_PARADO)
    {
        estado = PARADO;
    }
    else if (estado == DISPARANDO_SALTANDO)
    {
        estado = SALTANDO;
    }
}

void Protagonista::chocar(int dir)
{
    if (dir == IZQUIERDA)
    {
        estado = HERIDO;
        direccion = IZQUIERDA;
        b2Vec2 fuerza(-1*potenciaChoque, 1*potenciaSalto/2);
        b2Vec2 v(0.0f, 0.0f);
        fisica->SetLinearVelocity(v);
        fisica->ApplyForce(fuerza, fisica->GetPosition());
        puedeSaltar = false;
    }
    else if (dir == DERECHA)
    {
        estado = HERIDO;
        direccion = DERECHA;
        b2Vec2 fuerza(1*potenciaChoque, 1*potenciaSalto/2);
        b2Vec2 v(0.0f, 0.0f);
        fisica->SetLinearVelocity(v);
        fisica->ApplyForce(fuerza, fisica->GetPosition());
        puedeSaltar = false;
    }
    else
    {
        cerr << "Error Protagonista::CHOCAR, direccion desconocida" << endl;
    }
}

void Protagonista::recuperar()
{
    estado = PARADO;
}

void Protagonista::inicializarAnimaciones()
{
    wstring ruta = Gosu::sharedResourcePrefix() + L"media/animaciones/protagonista/";

    // Parado
    for (int i = 1; i <= 4; i++)
    {
        wstring rutaFinal = ruta + L"parado/protagonista" + boost::lexical_cast<wstring>(i) + L".png";
        animacionParado->anyadirImagen(rutaFinal);
    }

    // Movimiento izquierda 
    for (int i = 3; i <= 12; i++)
    {
        wstring rutaFinal = ruta + L"movIzquierda/protagonista" + boost::lexical_cast<wstring>(i) + L".png";
        animacionMI->anyadirImagen(rutaFinal);
    }

    // Movimiento derecha
    for (int i = 3; i <= 12; i++)
    {
        wstring rutaFinal = ruta + L"movDerecha/protagonista" + boost::lexical_cast<wstring>(i) + L".png";
        animacionMD->anyadirImagen(rutaFinal);
    }

    // Salto izquierda
    for (int i = 1; i <= 5; i++)
    {
        wstring rutaFinal = ruta + L"saltando_izq/protagonista" + boost::lexical_cast<wstring>(i) + L".png";

        for (int j = 0; j < 4; j++)
        {
            animacionSaltarI->anyadirImagen(rutaFinal);
        }
    }

    // Salto derecha
    for (int i = 1; i <= 5; i++)
    {
        wstring rutaFinal = ruta + L"saltando_der/protagonista" + boost::lexical_cast<wstring>(i) + L".png";

        for (int j = 0; j < 4; j++)
        {
            animacionSaltarD->anyadirImagen(rutaFinal);
        }
    }

    // Disparando izquierda
    for (int i = 3; i <= 12; i++)
    {
        wstring rutaFinal = ruta + L"movIzquierda_disparo/protagonista" + boost::lexical_cast<wstring>(i) + L".png";
        animacionDispararI->anyadirImagen(rutaFinal);
    }

    // Disparando derecha
    for (int i = 3; i <= 12; i++)
    {
        wstring rutaFinal = ruta + L"movDerecha_disparo/protagonista" + boost::lexical_cast<wstring>(i) + L".png";
        animacionDispararD->anyadirImagen(rutaFinal);
    }

    // Disparando y saltando a la izquierda
    for (int i = 1; i <= 5; i++)
    {
        wstring rutaFinal = ruta + L"saltando_disparo_izq/protagonista" + boost::lexical_cast<wstring>(i) + L".png";

        animacionDispSaltI->anyadirImagen(rutaFinal);
    }

    // Disparando y saltando a la derecha
    for (int i = 1; i <= 5; i++)
    {
        wstring rutaFinal = ruta + L"saltando_disparo_der/protagonista" + boost::lexical_cast<wstring>(i) + L".png";

        animacionDispSaltD->anyadirImagen(rutaFinal);
    }

    // Chocando izquierda
    for (int i = 1; i <= 5; i++)
    {
        wstring rutaFinal = ruta + L"choque_izq/protagonista" + boost::lexical_cast<wstring>(i) + L".png";

        animacionChoqueI->anyadirImagen(rutaFinal);
    }

    // Chocando derecha
    for (int i = 1; i <= 5; i++)
    {
        wstring rutaFinal = ruta + L"choque_der/protagonista" + boost::lexical_cast<wstring>(i) + L".png";

        animacionChoqueD->anyadirImagen(rutaFinal);
    }

}

Animacion* Protagonista::getAnimacionMI() const
{
    return animacionMI;
}

Animacion* Protagonista::getAnimacionMD() const
{
    return animacionMD;
}

Animacion* Protagonista::getAnimacionParado() const
{
    return animacionParado;
}

bool Protagonista::getPuedeSaltar() const
{
    return puedeSaltar;
}

void Protagonista::setPuedeSaltar(bool puede)
{
    puedeSaltar = puede;
}

void Protagonista::sufrirDanyo(int danyo)
{
    if (DatosPartida::getInstancia()->getEscudo() > 0)
    {
        DatosPartida::getInstancia()->setEscudo(DatosPartida::getInstancia()->getEscudo() - danyo);
    }
    else
    {
        DatosPartida::getInstancia()->setVida(DatosPartida::getInstancia()->getVida() - danyo);
    }
}

int Protagonista::getDireccion() const
{
    return direccion;
}

void Protagonista::reiniciarContactos()
{
    contraParedAbajo = false;
    contraParedArriba = false;
    contraParedDer = false;
    contraParedIzq = false;
}