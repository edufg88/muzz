#include "ElementoGUI.h"
#include "Juego.h"

ElementoGUI::ElementoGUI(int x, int y)
{
    setPos(x, y);
    setVisible(true);
}

ElementoGUI::~ElementoGUI()
{

}

void ElementoGUI::setPos(int x, int y)
{
    Juego *j = Juego::getInstancia();

    posX = x;
    posY = y;

    if (x > j->graphics().width())
    {
        posX = j->graphics().width();
    }
    if (x < 0)
    {
        posX = 0;
    }
    if (y < 0)
    {
        posY = 0;
    }
    if (y > j->graphics().height())
    {
        posY = j->graphics().height();
    }
}

int ElementoGUI::getX() const
{
    return posX;
}

int ElementoGUI::getY() const
{
    return posY;
}

bool ElementoGUI::esVisible() const
{
    return visible;
}

void ElementoGUI::setVisible(bool pVisible)
{
    visible = pVisible;
}