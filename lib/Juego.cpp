#include "Juego.h"
#include "Estados/EstadoMenu.h"
#include "Estados/EstadoPartida.h"
#include "Estados/EstadoCancion.h"
#include "Estados/EstadoGameOver.h"
#include "Estados/EstadoFin.h"
#include "Estados/EstadoTutorial.h"
#include "Animacion.h"

Juego* Juego::instancia = NULL;

Juego* Juego::getInstancia()
{
    if (instancia == NULL)
    {
        instancia = new Juego();
    }

    return instancia;
}

Juego::Juego() : Window(800, 600, false) 
{
    ultimoBeat = 0;
    jugando =  false;
    pausado = false;
    // Título de la ventana
    setCaption(L"Proyectito");
    // Audio
    audio = InterfazAudio::getInstancia();
    // Fisica
    fisica = InterfazFisica::getInstancia();
    // Procesador de audio
    procesadorAudio = new ProcesadorAudio();
    // IA
    ia = InterfazIA::getInstancia();
}

Juego::~Juego()
{
    if (estado != NULL)
    {
        delete estado;
    }
    estado = NULL;

    limpiar();
}

void Juego::limpiar()
{
    /**
     * En este destructor borramos todas las instancias SINGLETON
     */
    if (audio != NULL)
    {
        delete audio;
    }
    audio = NULL;
    if (fisica != NULL)
    {
        delete fisica;
    }
    fisica = NULL;
    if (procesadorAudio != NULL)
    {
        delete procesadorAudio;
    }
    procesadorAudio = NULL;
//    if (ia != NULL)
//    {
//        delete ia;
//    }
//    ia = NULL;

    if (panelPausa != NULL)
    {
        delete panelPausa;
    }
    panelPausa = NULL;
}

void Juego::reiniciar()
{
    audio->stopCancion();
    if (fisica != NULL)
        delete fisica;
    fisica = InterfazFisica::getInstancia();
    fisica->crearMundo();
//    limpiar();
//    cout << "REINICIO" << endl;
//     // Audio
//    audio = InterfazAudio::getInstancia();
//    // Fisica
//    fisica = InterfazFisica::getInstancia();
//    // Procesador de audio
//    procesadorAudio = new ProcesadorAudio();
    // IA
    //ia = InterfazIA::getInstancia();
    
    inicializar();
}

void Juego::inicializar()
{
    //cout << "INICIALIZO" << endl;
    // Inicializamos el audio
    audio->inicializarAudio();
    // Inicializamos la física
    fisica->crearMundo();
    // Inicializamos el estado
    // Estado menu
    if (estado == NULL)
    {
        cambiarEstado(ESTADO_MENU);
    }

    // Creamos el panel de pausa
    Animacion* a = new Animacion();
    a->anyadirImagen(L"media/imagenes/partida/fondos/fondopausa.png");
    panelPausa = new Panel(0, 0);
    panelPausa->setAnimacion(a);
}

void Juego::update()
{
    if (!pausado)
    {
        //cout << "ACTU JUEGO" << endl;
        audio->actualizar();
        procesadorAudio->update();
        procesadorAudio->process();
        if (jugando)
            fisica->actualizar();
        estado->actualizar();
    }
}

void Juego::draw()
{
    if (pausado && jugando)
    {
        panelPausa->pintar();
    }
    else
    {
        estado->pintar();
    }
}

bool Juego::cambiarEstado(int pEstado)
{
    cout << "ENTRAR" << endl;
    if (estado != NULL)
    {
        estado->salir();
        delete estado;
    }

    switch (pEstado)
    {
        case ESTADO_MENU:
            estado = new EstadoMenu();
            break;
        case ESTADO_CANCION:
            estado = new EstadoCancion();
            break;
        case ESTADO_PARTIDA:
            estado = new EstadoPartida();
            break;
        case ESTADO_GAMEOVER:
            estado = new EstadoGameOver();
            break;
        case ESTADO_FIN:
            estado = new EstadoFin();
            break;
        case ESTADO_TUTORIAL:
            estado = new EstadoTutorial();
            break;
    }
    
    estado->entrar();

    return true;
}

/**
 * FUNCIONES PARA LA CAPTURA DE EVENTOS
 * @param btn
 */

void Juego::buttonDown(Gosu::Button btn)
{
    if (btn == Gosu::kbEscape)
    {
        if (pausado == true)
        {
            audio->setPaused(false);
            pausado = false;
        }
        else if (jugando)
        {
            audio->setPaused(true);
            pausado = true;
        }
    }

    if (pausado)
    {
        if (btn == Gosu::kbQ)
        {
            close();
        }
        else if (btn == Gosu::kbM)
        {
            cambiarEstado(ESTADO_MENU);
            pausado = false;
        }
    }

    estado->buttonDown(btn);
}

void Juego::buttonUp(Gosu::Button btn)
{
    estado->buttonUp(btn);
}

void Juego::ejecutarBeat(int tipo)
{
    estado->ejecutarBeat(tipo);

    if (tipo == BASSBEAT)
    {
        ultimoBeat = Gosu::milliseconds();
    }
}

Protagonista* Juego::getProtagonista() const
{
    return dynamic_cast<EstadoPartida*>(estado)->getProtagonista();
}

bool Juego::getJugando () const
{
    return jugando;
}

void Juego::setJugando(bool jugando)
{
    this->jugando = jugando;
}

void Juego::salir()
{
    close();
}

void Juego::analizarCancion()
{
    procesadorAudio->firstAnalysis();
}

void Juego::setFinalizado()
{
    dynamic_cast<EstadoPartida*>(estado);
}