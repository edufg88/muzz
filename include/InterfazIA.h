#ifndef INTERFAZ_IA_H
#define INTERFAZ_IA_H

#include "LD/FuzzyModule.h"
#include "DatosCancion.h"
#include <iostream>
#include <map>
using namespace std;

// Tipos de nivel
#define RECOGIDA_ESTRELLAS 1
#define DESTRUIR_ENEMIGOS 2
#define SUPERVIVENCIA 3
#define CONSEGUIR_PUNTOS 4

class InterfazIA
{
    public:
        static InterfazIA* getInstancia();
        ~InterfazIA();
        
        /****
         MÉTODOS DE EVALUACIÓN DE REGLAS -> MOTOR DE LÓGICA DIFUSA
         ****/
        // Función para evaluar el tipo de nivel que se generará
        int getTipoNivel(string nombreModulo);
        // Función para evaluar el tipo de comportamiento de los enemigos
        int evComportamientoEnemigos();

    private:
        // Aquí almacenamos los distintios módulos de LD que necesitemos
        map<string, FuzzyModule*> modulosLD;
        // Evaluacion del tipo de nivel
        void initTN (string nombreModulo);
        // Deseabilidad de que el nivel sea de recogida de estrellas
        int getDeseabilidadTN1(string nombreModulo, int duracion, int genero, int estadoAnimo);
        // Deseabilidad de que el nivel sea de destrucción enemigos
        int getDeseabilidadTN2(string nombreModulo, int duracion, int genero, int estadoAnimo);
        // Deseabilidad de que el nivel sea de supervivencia
        int getDeseabilidadTN3(string nombreModulo, int duracion, int genero, int estadoAnimo);
        // Deseabilidad de que el nivel sea de consecución de puntos
        int getDeseabilidadTN4(string nombreModulo, int duracion, int genero, int estadoAnimo);


        static InterfazIA* instancia;
        InterfazIA();

        // Devuelve el nivel de intensidad de un género según agrupaciones previas
        // nivel de 0 a 100
        int getIntensidadGenero(int genero);
        int aleatorio(int min, int max);
        int maximo(int* v, int tam);
};

#endif