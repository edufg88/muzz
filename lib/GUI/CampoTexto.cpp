#include "GUI/CampoTexto.h"
#include "Juego.h"

CampoTexto::CampoTexto(wstring pFuente, wstring pTextoInicial, int tamTexto, int x, int y) : ElementoGUI(x, y), fuente(Juego::getInstancia()->graphics(), pFuente, tamTexto)
{
    texto = pTextoInicial;
    setTexto(pTextoInicial);
    tamanyo = tamTexto;
}

CampoTexto::~CampoTexto()
{

}

void CampoTexto::setTexto(wstring pTexto)
{
    setText(pTexto);
    texto = pTexto;
}

wstring CampoTexto::getTexto() const
{
    return texto;
}

double CampoTexto::ancho() const
{
    return fuente.textWidth(text());
}

double CampoTexto::alto() const
{
    return fuente.height();
}

bool CampoTexto::mouseOver() const
{
    double xRaton = Juego::getInstancia()->input().mouseX();
    double yRaton = Juego::getInstancia()->input().mouseY();

    return (xRaton > posX - PADDING && xRaton < posX + ancho() + PADDING &&
            yRaton > posY - PADDING && yRaton < posY + alto() + PADDING);
}

void CampoTexto::actualizar()
{

}

void CampoTexto::pintar()
{
    if (visible)
    {
        Juego* j = Juego::getInstancia();
        // Depending on whether this is the currently selected input or not, change the
        // background's color.
        Gosu::Color backgroundColor;

        if (j->input().textInput() == this)
            backgroundColor = ACTIVE_COLOR;
        else
            backgroundColor = INACTIVE_COLOR;

        j->graphics().drawQuad(posX - PADDING, posY - PADDING, backgroundColor,
                               posX + ancho() + PADDING, posY - PADDING, backgroundColor,
                               posX - PADDING, posY + alto() + PADDING, backgroundColor,
                               posX + ancho() + PADDING, posY + alto() + PADDING, backgroundColor, ZGUI);

        // Calculate the position of the caret and the selection start.
        double pX = posX + fuente.textWidth(text().substr(0, caretPos()));
        double sX = posX + fuente.textWidth(text().substr(0, selectionStart()));

        // Draw the selection background, if any; if not, sel_x and pos_x will be
        // the same value, making this quad empty.
        j->graphics().drawQuad(sX, posY, SELECTION_COLOR,
                               pX, posY, SELECTION_COLOR,
                               sX, posY + alto(), SELECTION_COLOR,
                               pX, posY + alto(), SELECTION_COLOR, ZGUI);

        // Draw the caret; again, only if this is the currently selected field.
        if (j->input().textInput() == this)
            j->graphics().drawLine(pX, posY, CARET_COLOR,
                                   pX, posY + alto(), CARET_COLOR, ZGUI);

        // Finally, draw the text itself!
        fuente.draw(text(), posX, posY, ZGUI);
    }
}