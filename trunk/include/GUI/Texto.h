#ifndef TEXTO_H
#define TEXTO_H

#include "ElementoGUI.h"
#include "GosuAux.h"
using namespace std;

class Texto : public ElementoGUI
{
    public:
        Texto(wstring pFuente, wstring pTexto, int tam, int x, int y);
        ~Texto();
        void setTexto (wstring pTexto);
        wstring getTexto () const;

        // Heredadas
        void actualizar();
        void pintar();

    private:
        Gosu::Font fuente;
        wstring texto;
        int tamanyo;
};

#endif