#ifndef GENERADOR_NIVELES_H
#define GENERADOR_NIVELES_H

#include "Nivel.h"
#include "InterfazIA.h"
#include <tinyxml.h>

class GeneradorNiveles
{
    public:
        static GeneradorNiveles* getInstancia();
        ~GeneradorNiveles();
        Nivel* generar();

    private:
        static GeneradorNiveles* instancia;
        GeneradorNiveles();

        // Generadores de niveles particulares
        Nivel* GenRecogidaEstrellas();
        Nivel* GenDestruirEnemigos();
        Nivel* GenSupervivencia();
        Nivel* GenConseguirPuntos();

        // Lee los datos del fichero
        void leerNivel(Nivel* n, int tipo);
};

#endif