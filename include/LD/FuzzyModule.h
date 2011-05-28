#ifndef FUZZY_MODULE_H
#define FUZZY_MODULE_H

#include <map>
#include <vector>
#include "LD/FuzzyRule.h"
#include "LD/FuzzyVariable.h"
#include "LD/FuzzyTerm.h"
using namespace std;

class FuzzyModule
{
    public:
        // Utilizaremos 2 posibles métodos de defuzzificación: centroide o max_av
        enum DefuzzifyType{max_av, centroid};
        // Número de muestras en el caso de calcular con el centroide
        enum {NumSamplesToUseForCentroid = 15};

        ~FuzzyModule();
        // Crea una variable nueva
        FuzzyVariable* CreateFLV(const std::string& VarName);
        // Añade una nueva regla al módulo: ant -> cons
        void AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence);

        void Fuzzify(const string& NameOfFLV, double val);
        double DeFuzzify(const string& key, DefuzzifyType method);

    private:
        // Definimos un tipo para controlar las variables difusas
        typedef map<string, FuzzyVariable*> VarMap;
        // Map que contiene las variables difusas
        VarMap m_Variables;
        // Vector que contiene las reglas difusas
        vector<FuzzyRule*> m_Rules;
        // Utilizada por el método Defuzzify()
        void SetConfidencesOfConsequentsToZero();
};

#endif