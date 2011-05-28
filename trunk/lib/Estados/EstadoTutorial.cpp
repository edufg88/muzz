#include "Estados/EstadoTutorial.h"
#include "Estados/EstadoMenu.h"
#include "Juego.h"

EstadoTutorial::EstadoTutorial()
{
    cout << "CONSTRUCTOR Estado Tutorial" << endl;
    pagina = 0;
    wstring filename = Gosu::sharedResourcePrefix() + L"media/imagenes/tutorial/0.png";
    fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), filename, false));

    bAnterior = NULL;
    bSiguiente = NULL;
}

EstadoTutorial::~EstadoTutorial()
{
    if (bAnterior != NULL)
        delete bAnterior;
    bAnterior = NULL;

    if (bSiguiente != NULL)
        delete bSiguiente;
    bSiguiente = NULL;
}

void EstadoTutorial::entrar()
{
    cout << "Entro en Estado Tutorial" << endl;
    // Indicamos al juego que NO estamos jugando
    Juego::getInstancia()->setJugando(false);
    inicializarGUI();
}

void EstadoTutorial::actualizar()
{

}

void EstadoTutorial::pintar()
{
    fondo->draw(0, 0, ZFONDO);
    pintarGUI();
}

void EstadoTutorial::salir()
{
    cout << "Salgo de Estado Tutorial" << endl;
}

void EstadoTutorial::buttonDown(Gosu::Button btn)
{
    Juego* j = Juego::getInstancia();

    if (btn == Gosu::msLeft)
    {
        if (bAnterior->mouseOver())
        {
            paginaAnterior();
        }
        else if (bSiguiente->mouseOver())
        {
            paginaSiguiente();
        }
    }

    if (btn == Gosu::kbEscape)
    {
        j->cambiarEstado(ESTADO_MENU);
    }
}
void EstadoTutorial::buttonUp(Gosu::Button btn)
{

}

void EstadoTutorial::leerInput()
{

}

void EstadoTutorial::ejecutarBeat(int tipo)
{

}

void EstadoTutorial::paginaSiguiente()
{
    if (pagina < 4)
    {
        pagina++;
        wstring filename = Gosu::sharedResourcePrefix() + L"media/imagenes/tutorial/" + boost::lexical_cast<wstring>(pagina) + L".png";
        fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), filename, false));
    }
}

void EstadoTutorial::paginaAnterior()
{
    if (pagina > 0)
    {
        pagina--;
        wstring filename = Gosu::sharedResourcePrefix() + L"media/imagenes/tutorial/" + boost::lexical_cast<wstring>(pagina) + L".png";
        fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), filename, false));
    }
}

void EstadoTutorial::inicializarGUI()
{
    wstring aux;
    Animacion* aAnt = new Animacion();
    Animacion* aSig = new Animacion();

    aux = Gosu::sharedResourcePrefix() + L"media/imagenes/tutorial/";
    aAnt->anyadirImagen(aux + L"anterior.png");
    aSig->anyadirImagen(aux + L"siguiente.png");

    bAnterior = new Boton(aAnt, 50, 550);
    bSiguiente = new Boton(aSig, 600, 550);

}

void EstadoTutorial::pintarGUI()
{
    bAnterior->pintar();
    bSiguiente->pintar();
}