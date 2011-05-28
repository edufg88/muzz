#ifndef CAMPO_TEXTO_H
#define CAMPO_TEXTO_H
#include "ElementoGUI.h"
#include "GosuAux.h"
using namespace std;

class CampoTexto : public ElementoGUI, public Gosu::TextInput
{
    public:
        static const unsigned long INACTIVE_COLOR  = 0xcc666666;
        static const unsigned long ACTIVE_COLOR    = 0xccff6666;
        static const unsigned long SELECTION_COLOR = 0xcc0000ff;
        static const unsigned long CARET_COLOR     = 0xffffffff;
        static const int PADDING = 5;

        CampoTexto(wstring pFuente, wstring pTextoInicial, int tamTexto, int x, int y);
        ~CampoTexto();
        void setTexto(wstring pTexto);
        wstring getTexto() const;
        double ancho() const;
        double alto() const;
        bool mouseOver() const;
        void actualizar();
        void pintar();

    private:
        Gosu::Font fuente;
        wstring texto;
        int tamanyo;
};

#endif