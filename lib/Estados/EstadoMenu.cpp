#include "Estados/EstadoMenu.h"
#include "Juego.h"
#include "Estados/EstadoCancion.h"

EstadoMenu::EstadoMenu()
{
    cout << "CONSTRUCTOR Estado MENU" << endl;
    wstring filename = Gosu::sharedResourcePrefix() + L"media/imagenes/menu/fondomenu.bmp";
    fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), filename, false));

    botonJugar = NULL;
    botonHTP = NULL;
    botonSalir = NULL;
}

EstadoMenu::~EstadoMenu()
{
    cout << "DESTRUCTOR ESTADO MENU" << endl;
    if (botonJugar != NULL)
        delete botonJugar;
    botonJugar = NULL;
    if (botonHTP != NULL)
        delete botonHTP;
    botonHTP = NULL;
    if (botonSalir != NULL)
        delete botonSalir;
    botonSalir = NULL;
}

void EstadoMenu::entrar()
{
    cout << "Entro en Estado Menu" << endl;
    // Indicamos al juego que NO estamos jugando
    Juego::getInstancia()->setJugando(false);
    inicializarGUI();
}

void EstadoMenu::actualizar()
{
    leerInput();
}

void EstadoMenu::pintar()
{
    fondo->draw(0,0,ZFONDO);
    pintarGUI();
}

void EstadoMenu::salir()
{
    cout << "Salgo de Estado Menu" << endl;
}

void EstadoMenu::buttonDown(Gosu::Button btn)
{
    Juego* j = Juego::getInstancia();

    if (btn == Gosu::msLeft)
    {
        if (botonJugar->mouseOver())
        {
            j->cambiarEstado(ESTADO_CANCION);
        }
        else if (botonHTP->mouseOver())
        {
            j->cambiarEstado(ESTADO_TUTORIAL);
        }
        else if (botonSalir->mouseOver())
        {
            j->salir();
        }
    }
}

void EstadoMenu::buttonUp(Gosu::Button btn)
{

}

void EstadoMenu::leerInput()
{

}

void EstadoMenu::inicializarGUI()
{
    wstring aux;
    Animacion* bj = new Animacion();
    Animacion* bhtp = new Animacion();
    Animacion* bs = new Animacion();

    aux = Gosu::sharedResourcePrefix() + L"media/imagenes/menu/";
    // Botón jugar
    bj->anyadirImagen(aux + L"botonjugar.png");
    // Botón De que va?
    bhtp->anyadirImagen(aux + L"botonhtp.png");
    // Botón salir
    bs->anyadirImagen(aux + L"botonsalir.png");

    botonJugar = new Boton(bj, 300, 340);
    botonHTP = new Boton(bhtp, 300, 410);
    botonSalir = new Boton(bs, 300, 480);
}

void EstadoMenu::pintarGUI()
{
    botonJugar->pintar();
    botonHTP->pintar();
    botonSalir->pintar();
}

void EstadoMenu::ejecutarBeat(int tipo)
{

}