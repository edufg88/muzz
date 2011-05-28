#ifndef FUZZYVARIABLE_H
#define FUZZYVARIABLE_H

#include "LD/FzSet.h"
#include <map>
#include <iostream>
using namespace std;

class FuzzyVariable
{
    public:
        FuzzyVariable():m_dMinRange(0.0),m_dMaxRange(0.0){}

        /**
         * Estos métodos crean instancias de conjuntos y los añaden a los maps.
         * Cada vez que se crea y añade un conjunto del tipo que sea se reajustan los
         * rangos. Todos los métodos devuelven un proxy al conjunto que puede ser utilizado
         * como operando cuando se crea la regla base.
         */
        FzSet AddLeftShoulderSet(string name, double minBound, double peak, double maxBound);
        FzSet AddRightShoulderSet(string name, double minBound, double peak, double maxBound);
        FzSet AddTriangularSet(string name, double minBound, double peak, double maxBound);
        FzSet AddTrapeziumSet(string name, double minBound, double peak1, double peak2, double maxBound);
        FzSet AddSingletonSet(string name, double minBound, double peak, double maxBound);

        // Fuzzifica el valor calculando su DOM en cada uno de los conjuntos de la variable
        void Fuzzify(double val);
        // Defuzzifica utilizando MaxAv
        double DeFuzzifyMaxAv()const;
        // Defuzzifica utilizando Centroide
        double DeFuzzifyCentroid(int NumSamples)const;

    private:
        // Tipo creado para conjuntos
        typedef map<string, FuzzySet*> MemberSets;
        // Prohibimos copias y asignaciones
        FuzzyVariable(const FuzzyVariable&);
        FuzzyVariable& operator=(const FuzzyVariable&);
        // Map de conjuntos difusos que tiene la variable
        MemberSets m_MemberSets;
        // Mínimos y máximos del rango
        double m_dMinRange;
        double m_dMaxRange;
        // Método llamado para reajustar los rangos cada vez que se añade un conjunto
        void AdjustRangeToFit(double min, double max);
        // Controlamos el borrado de las variables
        ~FuzzyVariable();
        friend class FuzzyModule;
};


#endif