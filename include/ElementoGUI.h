#ifndef ELEMENTO_GUI_H
#define ELEMENTO_GUI_H

class ElementoGUI
{
    public:
        ElementoGUI(int x, int y);
        virtual ~ElementoGUI() = 0;
        void setPos(int x, int y);
        int getX() const;
        int getY() const;
        bool esVisible() const;
        void setVisible(bool pVisible);
        virtual void actualizar() = 0;
        virtual void pintar() = 0;

    protected:
        int posX;
        int posY;
        bool visible;
};

#endif