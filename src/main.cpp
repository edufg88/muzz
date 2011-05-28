#include <iostream>
#include "Juego.h"
#include <unistd.h>
#include "InterfazIA.h"
#include "DatosCancion.h"
using namespace std;


int main ()
{
    Juego *j = NULL;

    j = Juego::getInstancia();
    j->inicializar();
    j->show();

    if (j != NULL)
        delete j;
    j = NULL;

    /*
    InterfazIA* ia = InterfazIA::getInstancia();
    ia->initTN("modulo1");
    int i1 = ia->getDeseabilidadTN1("modulo1", 240, POP, 55);
    int i2 = ia->getDeseabilidadTN2("modulo1", 240, POP, 55);
    int i3 = ia->getDeseabilidadTN3("modulo1", 240, POP, 55);
    int i4 = ia->getDeseabilidadTN4("modulo1", 240, POP, 55);

    cout << i1 << " " << i2  << " " << i3 << " " << i4 << endl;
    */
    return 0;
}