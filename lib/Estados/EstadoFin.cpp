#include "Estados/EstadoFin.h"
#include "Estados/EstadoMenu.h"
#include "Juego.h"

EstadoFin::EstadoFin()
{
    cout << "CONSTRUCTOR Estado FIN" << endl;
    wstring filename = Gosu::sharedResourcePrefix() + L"media/imagenes/fin/fondofin.png";
    fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), filename, false));
}

EstadoFin::~EstadoFin()
{

}

void EstadoFin::entrar()
{
    cout << "Entro en Estado Fin" << endl;
    // Indicamos al juego que NO estamos jugando
    Juego::getInstancia()->setJugando(false);
}

void EstadoFin::actualizar()
{

}

void EstadoFin::pintar()
{
    fondo->draw(0, 0, ZFONDO);
}

void EstadoFin::salir()
{
    cout << "Salgo de Estado Fin" << endl;
}

void EstadoFin::buttonDown(Gosu::Button btn)
{
    if (btn == Gosu::kbQ)
    {
        Juego::getInstancia()->salir();
    }
    else if (btn == Gosu::kbM)
    {
        Juego::getInstancia()->cambiarEstado(ESTADO_MENU);
    }
}
void EstadoFin::buttonUp(Gosu::Button btn)
{

}

void EstadoFin::leerInput()
{

}

void EstadoFin::ejecutarBeat(int tipo)
{

}
