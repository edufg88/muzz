#include "Estados/EstadoPartida.h"
#include "Juego.h"
#include "Protagonista.h"
#include "Animacion.h"
#include "Nivel.h"
#include "InterfazAudio.h"
#include "ObjetoFijo.h"
#include "DatosCancion.h"
#include <math.h>
#include "GeneradorNiveles.h"

void EstadoPartida::inicializarProtagonista()
{
    cout << "inicializo prota" << endl;
    personaje = new Protagonista("protagonista", 20, 0);
}

EstadoPartida::EstadoPartida()
{
    cout << "Constructor ESTADO PARTIDA " << endl;
    // Inicializamos el protagonista
    inicializarProtagonista();
    // Creamos una instancia de los datos de la partida
    datosPartida = DatosPartida::getInstancia();
    // Nivel
    nivel = GeneradorNiveles::getInstancia()->generar();
    // Inicializamos la posición de la cámara
    camara = new Camara(0, 0);
    // Inicializamos el GUI
    panelCara = NULL;
    panelVida = NULL;
    panelEscudo = NULL;
    textoPuntos = NULL;
    puntuacion = NULL;
    textoInicial = NULL;
}

EstadoPartida::~EstadoPartida()
{
    cout << "DESTRUCTOR ESTADO PARTIDA" << endl;
    if (datosPartida != NULL)
    {
        delete datosPartida;
    }
    datosPartida = NULL;

    if (camara != NULL)
    {
        delete camara;
    }
    camara = NULL;
//    if (personaje != NULL)
//    {
//        delete personaje;
//    }
//    personaje = NULL;
//    if (nivel != NULL)
//    {
//        delete nivel;
//    }
//    nivel = NULL;

    // Parte del GUI
    if (panelCara != NULL)
        delete panelCara;
    panelCara = NULL;
    if (panelVida != NULL)
        delete panelVida;
    panelVida = NULL;
    if (panelEscudo != NULL)
        delete panelEscudo;
    panelEscudo = NULL;
    if (textoPuntos != NULL)
        delete textoPuntos;
    textoPuntos = NULL;
    if (puntuacion != NULL)
        delete puntuacion;
    puntuacion = NULL;
    if (textoVolumen != NULL)
        delete textoVolumen;
    textoVolumen = NULL;
    if (volumen != NULL)
        delete volumen;
    volumen = NULL;
    if (textoPan != NULL)
        delete textoPan;
    textoPan = NULL;
    if (pan != NULL)
        delete pan;
    pan = NULL;
    if (duracion != NULL)
        delete duracion;
    duracion = NULL;
}

void EstadoPartida::entrar()
{
    cout << "Entro en Estado Partida" << endl;
    // Inicializamos GUI
    inicializarGUI();
    // Hacemos que la cámara enlace con el personaje para que le siga
    camara->enlazarCamara(personaje);
    // Establecemos los límites de movimiento para la cámara
    camara->setLimites(nivel->getAncho(), nivel->getAlto());
    // Cargamos la canción
    InterfazAudio::getInstancia()->playCancion();
    // Indicamos al juego que empieza la partida
    Juego::getInstancia()->setJugando(true);
}

void EstadoPartida::actualizar()
{
    //cout << "ACTU ESTADO PARTIDA" << endl;
    leerInput();
    camara->actualizar();
    actualizarGUI();
    if (Juego::getInstancia()->getJugando())
        nivel->actualizar();
    if (Juego::getInstancia()->getJugando())
        personaje->actualizar();
}

void EstadoPartida::pintar()
{
    Juego::getInstancia()->graphics().pushTransform(Gosu::translate(-camara->getX(), -camara->getY()));
    nivel->pintar();
    personaje->pintar();
    Juego::getInstancia()->graphics().popTransform();
    pintarGUI();
}

void EstadoPartida::salir()
{
    cout << "Salgo de Estado Partida" << endl;
//    if (personaje != NULL)
//        delete personaje;
//    personaje = NULL;
    if (nivel != NULL)
        delete nivel;
    nivel = NULL;
    Juego::getInstancia()->reiniciar();
}

void EstadoPartida::buttonDown(Gosu::Button btn)
{
    if (btn == Gosu::kbLeft)
    {
        //personaje->moverIzquierda();
    }
    if (btn == Gosu::kbRight)
    {
        //personaje->moverDerecha();
    }
    if (btn == Gosu::kbUp)
    {
        personaje->saltar();
    }
    if (btn == Gosu::kbSpace)
    {
        // Si le damos a disparar en un BEAT la bala será especial
        if ((Gosu::milliseconds() - Juego::getInstancia()->ultimoBeat) < 100)
        {
            personaje->disparar(true);
        }
        else
        {
            personaje->disparar(false);
        }
    }
    if (btn == Gosu::kbQ)
    {
        InterfazAudio::getInstancia()->getDatosCancion()->setVolumen(InterfazAudio::getInstancia()->getDatosCancion()->getVolumen()-0.1);
    }
    if (btn == Gosu::kbW)
    {
        InterfazAudio::getInstancia()->getDatosCancion()->setVolumen(InterfazAudio::getInstancia()->getDatosCancion()->getVolumen()+0.1);
    }
    if (btn == Gosu::kbA)
    {
        InterfazAudio::getInstancia()->getDatosCancion()->setPan(InterfazAudio::getInstancia()->getDatosCancion()->getPan()-0.1);
    }
    if (btn == Gosu::kbS)
    {
        InterfazAudio::getInstancia()->getDatosCancion()->setPan(InterfazAudio::getInstancia()->getDatosCancion()->getPan()+0.1);
    }
}

void EstadoPartida::buttonUp(Gosu::Button btn)
{
    if (btn == Gosu::kbLeft)
    {
        personaje->parar();
    }
    if (btn == Gosu::kbRight)
    {
        personaje->parar();
    }
    if (btn == Gosu::kbSpace)
    {
        personaje->pararDisparar();
    }
}

void EstadoPartida::leerInput()
{
    Juego *j = Juego::getInstancia();

    if (j->input().down(Gosu::kbLeft))
    {
        personaje->moverIzquierda();
    }
    if (j->input().down(Gosu::kbRight))
    {
        personaje->moverDerecha();
    }
    if (j->input().down(Gosu::kbK))
    {
        InterfazAudio::getInstancia()->cargarEfecto("burp.mp3", "burp");
    }
    if (j->input().down(Gosu::kbO))
    {
        InterfazAudio::getInstancia()->playEfecto("burp");
    }

}

void EstadoPartida::inicializarGUI()
{
    wstring aux;
    Animacion* pc = new Animacion();
    Animacion* pv = new Animacion();
    Animacion* pe = new Animacion();

    // Imágenes para las caras
    // -------------------------
    aux = Gosu::sharedResourcePrefix() + L"media/animaciones/protagonista/caras/";
    for (int i = 1; i <= 6; i++)
    {
        pc->anyadirImagen(aux + L"cara" + boost::lexical_cast<wstring>(i) + L".png");
    }
    pc->setIndiceImgActual(0);
    
    // Imagen para la barra de vida
    // -------------------------
    aux = Gosu::sharedResourcePrefix() + L"media/imagenes/partida/vida/";
    for (int i = 1; i <= 3; i++)
    {
        pv->anyadirImagen(aux + L"vida" + boost::lexical_cast<wstring>(i) + L".png");
    }
    pv->setIndiceImgActual(2);

    // Imagen para la barra de escudo
    // -------------------------
    aux = Gosu::sharedResourcePrefix() + L"media/imagenes/partida/escudo/";
    for (int i = 1; i <= 3; i++)
    {
        pe->anyadirImagen(aux + L"escudo" + boost::lexical_cast<wstring>(i) + L".png");
    }
    pe->setIndiceImgActual(2);

    // La puntuacion
    // -------------------------
    aux = L"media/fuentes/crayon.ttf";
    // Texto duración
    duracion = new Texto(aux, L"", 20, 700, 10);
    // Texto "Puntos:"
    textoPuntos = new Texto(aux, L"Puntos:", 20, 650, 40);
    // Texto que indica la puntuación
    puntuacion = new Texto (aux, boost::lexical_cast<wstring>(datosPartida->getPuntos()), 20, 730, 40);

    // El volumen y el pan
    // -------------------------
    textoVolumen = new Texto(aux, L"Vol: ", 20, 700, 550);
    volumen = new Texto(aux, L"0", 20, 750, 550);
    textoPan = new Texto(aux, L"Pan: ", 20, 700, 575);
    pan = new Texto(aux, L"0", 20, 750, 575);

    panelCara = new Panel(pc, 10, 10);
    panelVida = new Panel(pv, 70, 15);
    panelEscudo = new Panel(pe, 70, 45);

    // Texo para el mensaje inicial
    //------------------------------------
    switch (nivel->getTipo())
    {
        case RECOGIDA_ESTRELLAS:
            textoInicial = new Texto(aux, L"RECOGE TODAS LAS ESTRELLAS!", 40, 100, 250);
            break;
        case DESTRUIR_ENEMIGOS:
            textoInicial = new Texto(aux, L"DESTRUYE TODOS LOS ENEMIGOS!", 40, 100, 250);
            break;
        case SUPERVIVENCIA:
            textoInicial = new Texto(aux, L"SOBREVIVE TODO LO QUE PUEDAS!", 40, 100, 250);
            break;
        case CONSEGUIR_PUNTOS:
            textoInicial = new Texto(aux, L"CONSIGUE PUNTOS Y LLEGA A META!", 40, 100, 250);
            break;
    }
    timerTextoInicial = Gosu::milliseconds();
}

void EstadoPartida::actualizarGUI()
{
    if (datosPartida->getEscudo() == 0)
    {
        panelEscudo->setVisible(false);
    }
    if (datosPartida->getEscudo() < 30)
    {
        panelEscudo->getAnimacion()->setIndiceImgActual(0);
    }
    else if (datosPartida->getEscudo() < 65)
    {
        panelEscudo->getAnimacion()->setIndiceImgActual(1);
    }
    else
    {
        panelEscudo->getAnimacion()->setIndiceImgActual(2);
    }

    if (datosPartida->getVida() < 30)
    {
        panelVida->getAnimacion()->setIndiceImgActual(0);

        if (datosPartida->getEscudo() < 20)
        {
            panelCara->getAnimacion()->setIndiceImgActual(5);
        }
        else if (datosPartida->getEscudo() < 40)
        {
            panelCara->getAnimacion()->setIndiceImgActual(4);
        }
    }
    else if (datosPartida->getVida() < 65)
    {
        panelVida->getAnimacion()->setIndiceImgActual(1);

        if (datosPartida->getEscudo() < 20)
        {
            panelCara->getAnimacion()->setIndiceImgActual(3);
        }
        else if (datosPartida->getEscudo() < 40)
        {
            panelCara->getAnimacion()->setIndiceImgActual(2);
        }
        else
        {
            panelCara->getAnimacion()->setIndiceImgActual(1);
        }
    }
    else
    {
        panelVida->getAnimacion()->setIndiceImgActual(2);

        if (datosPartida->getEscudo() < 50)
            panelCara->getAnimacion()->setIndiceImgActual(1);
        else
            panelCara->getAnimacion()->setIndiceImgActual(0);
    }

    // Actualizamos la duración
    unsigned int ms;
    unsigned int mstotal;
    InterfazAudio::getInstancia()->getChannel()->getPosition(&ms, FMOD_TIMEUNIT_MS);
    mstotal = InterfazAudio::getInstancia()->getDatosCancion()->getDuracion();
    ms = mstotal - ms;

    if (ms/1000/60 < 10)
    {
        if (ms/1000%60 < 10)
        {
            duracion->setTexto(L"0" + boost::lexical_cast<wstring>(ms/1000/60) + L" : 0" + boost::lexical_cast<wstring>(ms/1000%60));
        }
        else
        {
            duracion->setTexto(L"0" + boost::lexical_cast<wstring>(ms/1000/60) + L" : " + boost::lexical_cast<wstring>(ms/1000%60));
        }
    }
    else
    {
        if (ms/1000%60 < 10)
        {
            duracion->setTexto(boost::lexical_cast<wstring>(ms/1000/60) + L" : 0" + boost::lexical_cast<wstring>(ms/1000%60));
        }
        else
        {
            duracion->setTexto(boost::lexical_cast<wstring>(ms/1000/60) + L" : " + boost::lexical_cast<wstring>(ms/1000%60));
        }
    }

    // Actualizamos los puntos
    puntuacion->setTexto(boost::lexical_cast<wstring>(datosPartida->getPuntos()));

    // Actualizamos el volumen y el pan
    volumen->setTexto(boost::lexical_cast<wstring>(static_cast<int>(InterfazAudio::getInstancia()->getDatosCancion()->getVolumen()*100)));
    pan->setTexto(boost::lexical_cast<wstring>(static_cast<int>(InterfazAudio::getInstancia()->getDatosCancion()->getPan()*100)));

    // Actualizamos el texto inicial
    if ((Gosu::milliseconds() - timerTextoInicial) > 5000)
    {
        textoInicial->setVisible(false);
    }
}

void EstadoPartida::pintarGUI()
{
    panelCara->pintar();
    panelVida->pintar();
    panelEscudo->pintar();
    duracion->pintar();
    textoPuntos->pintar();
    puntuacion->pintar();
    textoVolumen->pintar();
    volumen->pintar();
    textoPan->pintar();
    pan->pintar();
    textoInicial->pintar();
}

void EstadoPartida::ejecutarBeat(int tipo)
{
    // Ejecutamos el beat para el personaje
    switch (tipo)
    {
        case HIGHBEAT:
            break;
        case MIDBEAT:
            break;
        case BASSBEAT:
            nivel->ejecutarBeat(tipo);
            personaje->getAnimacionParado()->setIndiceImgActual(1);
            break; 
        default:
            personaje->getAnimacionParado()->setIndiceImgActual(0);
            break;
    }

    // Ejecutamos el beat para el nivel
    nivel->ejecutarBeat(tipo);
}

Protagonista* EstadoPartida::getProtagonista() const
{
    return personaje;
}

void EstadoPartida::setFinalizado()
{
    nivel->setFinalizado();
}