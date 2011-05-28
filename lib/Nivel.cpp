#include "Nivel.h"
#include "Juego.h"
#include "Animacion.h"
#include "ObjetoFijo.h"
#include "ConversorFisico.h"
#include "Estados/EstadoGameOver.h"
#include "Estados/EstadoFin.h"
#include "Enemigos/Triangulo.h"
#include "Objetos/Pico.h"
#include "Objetos/Roca.h"

Nivel::Nivel(int tipo)
{
    this->tipo = tipo;
    nObjs = 0;
    xFondo = 0;
    yFondo = 0;
    ancho = 0;
    alto = 0;
    timerPico = Gosu::milliseconds() + 10000;
    timerRoca = Gosu::milliseconds() + 5000;
    initPums();
    setFondo();
}

Nivel::Nivel(int tipo, wstring rutaFondo)
{
    finalizado = false;
    this->tipo = tipo;
    xFondo = 0;
    yFondo = 0;
    timerPico = Gosu::milliseconds() + 10000;
    timerRoca = Gosu::milliseconds() + 5000;
    setFondo(rutaFondo);
    initPums();
}

Nivel::~Nivel()
{
    // Eliminamos los objetos
    map<string, Objeto*>::iterator it;
    for (it = objetos.begin(); it != objetos.end(); it++)
    {
        Objeto* o = it->second;
        objetos.erase(it);
        if (o != NULL)
        {
            delete o;
        }
        o = NULL;
    }

    // Eliminamos los enemigos
    map<string, Enemigo*>::iterator it2;
    for (it2 = enemigos.begin(); it2 != enemigos.end(); it2++)
    {
        Enemigo* e = it2->second;
        enemigos.erase(it2);
        if (e != NULL)
        {
            delete e;
        }
        e = NULL;
    }
}

void Nivel::pintar()
{
    // Pintamos el fondo
    fondo->draw(xFondo, yFondo, ZFONDO);
    fondo->draw(xFondo + fondo->width() - 5, yFondo, ZFONDO);

    // Pintamos los objetos del nivel
    map<string, Objeto*>::iterator it;
    for (it = objetos.begin(); it != objetos.end(); it++)
    {
        it->second->pintar();
    }
    // Pintamos los enemigos del nivel
    map<string, Enemigo*>::iterator it2;
    for (it2 = enemigos.begin(); it2 != enemigos.end(); it2++)
    {
        it2->second->pintar();
    }

    // Pintamos los efectos de fondo
    pums.back()->getImagenActual()->drawRot(250, 100, ZFONDO, 0);
    pums.back()->getImagenActual()->drawRot(800, 120, ZFONDO, 0);
}

void Nivel::actualizarObjetos()
{
    // Actualizamos los objetos del nivel
    map<string, Objeto*>::iterator it;
    for (it = objetos.begin(); it != objetos.end(); it++)
    {
        // Si no está activo el objeto lo borramos
        if (it->second->esActivo() == false)
        {
            Objeto* obj = it->second;

            objetos.erase(it);

            if (obj != NULL)
            {
                delete obj;
            }
            obj = NULL;
        }
        else
        {
            it->second->actualizar();
        }
    }
}

void Nivel::actualizarEnemigos()
{
    // Actualizamos los enemigos del nivel
    map<string, Enemigo*>::iterator it2;
    for (it2 = enemigos.begin(); it2 != enemigos.end(); it2++)
    {
        // Si no está activo el enemigo lo borramos
        if (it2->second->esActivo() == false)
        {
            Enemigo* ene = it2->second;

            enemigos.erase(it2);
            if (ene != NULL)
            {
                delete ene;
            }
            ene = NULL;
        }
        else
        {
            it2->second->actualizar();
        }
    }
}

void Nivel::actualizarEstado()
{
    // Comprobamos que tiempo queda de partida
    unsigned int ms;
    unsigned int mstotal;
    InterfazAudio::getInstancia()->getChannel()->getPosition(&ms, FMOD_TIMEUNIT_MS);
    mstotal = InterfazAudio::getInstancia()->getDatosCancion()->getDuracion();
    ms = mstotal - ms;
    
    int cuenta = 0;
    map<string, Objeto*>::iterator it;

    switch (tipo)
    {
        case RECOGIDA_ESTRELLAS:
            // Contamos el número de estrellas que queda en el nivel
            for (it = objetos.begin(); (it != objetos.end()) && (cuenta == 0); it++)
            {
                // Si no está activo el objeto lo borramos
                if (it->second->getNombre() == "estrella")
                {
                    cuenta++;
                }
            }

            if (cuenta == 0)
            {
                // Cambiar estado, partida completada!!
                Juego::getInstancia()->cambiarEstado(ESTADO_FIN);
            }
            break;
            
        case DESTRUIR_ENEMIGOS:
            if (enemigos.empty())
            {
                // Cambiar estado, partida completada!!
                Juego::getInstancia()->cambiarEstado(ESTADO_FIN);
            }
            break;

        case SUPERVIVENCIA:
            if (ms == 0)
            {
                // Cambiar estado, partida completada!!
                Juego::getInstancia()->cambiarEstado(ESTADO_FIN);
            }
            break;

        case CONSEGUIR_PUNTOS:
            if (finalizado)
            {
                // Cambiar estado, partida completada!!
                Juego::getInstancia()->cambiarEstado(ESTADO_FIN);
            }
            break;
    }

    // Si nada de lo anterior se cumple y el tiempo se ha acabado, GAME OVER
    if (ms == 0)
    {
        //Juego::getInstancia()->cambiarEstado(new EstadoGameOver());
    }
}

void Nivel::actualizar()
{
    //actualizarLanzamientos();
    actualizarObjetos();
    actualizarEnemigos();
    actualizarEstado();
}

Objeto* Nivel::getObjeto(string key)
{
    return objetos[key];
}

void Nivel::setObjeto(string key, Objeto* objeto)
{
    objetos[key] = objeto;
}

Enemigo* Nivel::getEnemigo(string key)
{
    return enemigos[key];
}

void Nivel::setEnemigo(string key, Enemigo* enemigo)
{
    enemigos[key] = enemigo;
}

void Nivel::setFondo()
{
    // Primero obtenemos el género para cargar la imagen en funcion
    int genero = InterfazAudio::getInstancia()->getDatosCancion()->getGenero();

    wstring ruta = Gosu::sharedResourcePrefix() + L"media/imagenes/partida/fondos/";
    cout << "GENEROO: " << genero << endl;
    switch (genero)
    {
        case BLUES:
        case JAZZ:
        case R_AND_B:
        case SOUL:
            ruta += L"fondobjrs.bmp";
            break;

        case CLASSICAL:
        case CHILL_OUT:
            ruta += L"fondocc.bmp";
            break;

        case DANCE:
        case DISCO:
        case FUNK:
        case POP:
            ruta += L"fondoddfp.bmp";
            break;

        case PUNK:
        case METAL:
        case ROCK:
            ruta += L"fondopmr.bmp";
            break;

        case RAP:
        case REGGAE:
        case LATIN:
            ruta += L"fondorrl.bmp";
            break;

        case TECHNO:
        case SKA:
        case HOUSE:
            ruta += L"fondotsh.bmp";
            break;

        default:
            break;
    }

    fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), ruta, false));
}

void Nivel::setFondo(wstring rutaFondo)
{
    fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), rutaFondo, false));
}

int Nivel::getAncho() const
{
    return ancho;
}

int Nivel::getAlto() const
{
    return alto;
}

Objeto* Nivel::crearBloque(string nombre, float32 posX, float32 posY)
{
    ObjetoFijo* o = new ObjetoFijo("suelo", posX, posY);
    Animacion* a = new Animacion();
    a->anyadirImagen(Gosu::sharedResourcePrefix() + L"media/imagenes/partida/objetos/bloque.png");
    b2Body* body = InterfazFisica::getInstancia()->crearBox(ESTATICO, o, ConversorFisico::getMetersFromPixels(a->getImagen(0)->width()), ConversorFisico::getMetersFromPixels(a->getImagen(0)->height()), 3.0f, 3.0f, true, false);
    o->setFisica(body);
    o->setAnimacion(a);
    setObjeto(nombre, o);

    return o;
}

Objeto* Nivel::crearBloqueAux(string nombre, float32 posX, float32 posY)
{
    ObjetoFijo* o = new ObjetoFijo("bloque", posX, posY);
    Animacion* a = new Animacion();
    a->anyadirImagen(Gosu::sharedResourcePrefix() + L"media/imagenes/partida/objetos/bloque.png");
    b2Body* body = InterfazFisica::getInstancia()->crearBox(DINAMICO, o, a->getImagen(0)->width(), a->getImagen(0)->height(), 1.0f, 0.0f, true, false);
    o->setFisica(body);
    o->setAnimacion(a);
    setObjeto(nombre, o);

    return o;
}

void Nivel::crearSuelo()
{

    
}

void Nivel::ejecutarBeat(int tipo)
{
    map<string, Enemigo*>::iterator it;

    switch (tipo)
    {
        case HIGHBEAT:
            // Los beats altos lanzan una roca
            if ((Gosu::milliseconds() - timerPico) > 20000)
            {
                generarPico();
                timerPico = Gosu::milliseconds();
            }
            break;
        case MIDBEAT:
            // Los beats medios lanzan una roca
            if ((Gosu::milliseconds() - timerRoca) > 15000)
            {
                generarRoca();
                timerRoca = Gosu::milliseconds();
            }
            break;
        case BASSBEAT:
            // Cambiamos la animación de los triángulos
            for (it = enemigos.begin(); it != enemigos.end(); it++)
            {
                // Si no está activo el enemigo lo borramos
                if (it->second->getNombre() == "triangulo")
                {
                    Triangulo* t = dynamic_cast<Triangulo*>(it->second);
                    t->getAnimacionMI()->setIndiceImgActual(0);
                    t->getAnimacionMI()->setIndiceImgActual(0);
                }
            }

            pums.back()->setIndiceImgActual(1);
            break;
        default:
            // Cambiamos la animación de los triángulos
            for (it = enemigos.begin(); it != enemigos.end(); it++)
            {
                // Si no está activo el enemigo lo borramos
                if (it->second->getNombre() == "triangulo")
                {
                    Triangulo* t = dynamic_cast<Triangulo*>(it->second);
                    t->getAnimacionMI()->setIndiceImgActual(1);
                    t->getAnimacionMI()->setIndiceImgActual(1);
                }
            }
            pums.back()->setIndiceImgActual(0);
            break;
    }
}


void Nivel::initPums()
{
    int genero = InterfazAudio::getInstancia()->getDatosCancion()->getGenero();
    
    wstring ruta = Gosu::sharedResourcePrefix() + L"media/objetos/";

    switch (genero)
    {
        case BLUES:
        case JAZZ:
        case R_AND_B:
        case SOUL:
            ruta += L"blues-jazz-rnb-soul/";
            break;

        case CLASSICAL:
        case CHILL_OUT:
            ruta += L"classical-chillout/";
            break;

        case DANCE:
        case DISCO:
        case FUNK:
        case POP:
            ruta += L"dance-disco-funk-pop/";
            break;

        case PUNK:
        case METAL:
        case ROCK:
            ruta += L"punk-metal-rock/";
            break;

        case RAP:
        case REGGAE:
        case LATIN:
            ruta += L"rap-reggae-latin/";
            break;

        case TECHNO:
        case SKA:
        case HOUSE:
            ruta += L"techno-ska-house/";
            break;

        default:
            break;
    }

    // Temporal
    Animacion* a = new Animacion();
    a->anyadirImagen(Gosu::sharedResourcePrefix() + ruta + L"pum1.png");
    a->anyadirImagen(Gosu::sharedResourcePrefix() + ruta + L"pum2.png");
    pums.push_back(a);
}

void Nivel::setAncho(int a)
{
    ancho = a;
}

void Nivel::setAlto(int a)
{
    alto = a;
}

int Nivel::getTipo() const
{
    return tipo;
}

void Nivel::setFinalizado()
{
    finalizado = true;
}

void Nivel::actualizarLanzamientos()
{
    if ((Gosu::milliseconds() - timerPico) > 20000)
    {
        generarPico();
        timerPico = Gosu::milliseconds();
    }
    else if ((Gosu::milliseconds() - timerRoca) > 20000)
    {
        generarRoca();
        timerRoca = Gosu::milliseconds();
    }
}

void Nivel::generarPico()
{
    float xProta = Juego::getInstancia()->getProtagonista()->getX();

    Pico* p = new Pico("pico", xProta+10, -20);
    setObjeto("objeto" + boost::lexical_cast<string>(nObjs), p);
    nObjs++;
}

void Nivel::generarRoca()
{
    float xProta = Juego::getInstancia()->getProtagonista()->getX();

    Roca* r = new Roca("roca", xProta-10, -40);
    setObjeto("objeto" + boost::lexical_cast<string>(nObjs), r);
    nObjs++;
}