#include "Estados/EstadoGameOver.h"
#include "Estados/EstadoMenu.h"
#include "Juego.h"

EstadoGameOver::EstadoGameOver()
{
    cout << "CONSTRUCTOR Estado GAME OVER" << endl;
    wstring filename = Gosu::sharedResourcePrefix() + L"media/imagenes/gameover/fondogameover.png";
    fondo.reset(new Gosu::Image(Juego::getInstancia()->graphics(), filename, false));
}

EstadoGameOver::~EstadoGameOver()
{

}

void EstadoGameOver::entrar()
{
    cout << "Entro en Estado Game Over" << endl;
    // Indicamos al juego que NO estamos jugando
    Juego::getInstancia()->setJugando(false);
}

void EstadoGameOver::actualizar()
{

}

void EstadoGameOver::pintar()
{
    fondo->draw(0, 0, ZFONDO);
}

void EstadoGameOver::salir()
{
    cout << "Salgo de Estado Game Over" << endl;
}

void EstadoGameOver::buttonDown(Gosu::Button btn)
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

void EstadoGameOver::buttonUp(Gosu::Button btn)
{

}

void EstadoGameOver::leerInput()
{

}

void EstadoGameOver::ejecutarBeat(int tipo)
{

}
