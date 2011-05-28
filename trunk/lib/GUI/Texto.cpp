#include "GUI/Texto.h"
#include "Juego.h"

Texto::Texto(wstring pFuente, wstring pTexto, int tam, int x, int y) : ElementoGUI(x, y), fuente(Juego::getInstancia()->graphics(), pFuente, tam)
{
    texto = pTexto;
    tamanyo = tam;
}

Texto::~Texto()
{

}

void Texto::setTexto (wstring pTexto)
{
    texto = pTexto;
}

wstring Texto::getTexto () const
{
    return texto;
}

void Texto::actualizar()
{

}

void Texto::pintar()
{
    if (visible)
        fuente.draw(texto, posX, posY, ZGUI);
}
