#include <vector>
#include <assert.h>
#include "LD/FuzzyModule.h"
#include "LD/FuzzyVariable.h"
#include <iostream>

FuzzyModule::~FuzzyModule()
{
    // Liberamos las variables
    VarMap::iterator it;
    for (it = m_Variables.begin(); it != m_Variables.end(); it++)
    {
        FuzzyVariable* var = (*it).second;
        m_Variables.erase(it);
        if (var != NULL)
        {
            delete var;
            var = NULL;
        }
    }

    // Y las reglas
    vector<FuzzyRule*>::iterator it2;
    for (it2 = m_Rules.begin(); it2 != m_Rules.end(); it2++)
    {
        FuzzyRule* rule = *it2;
        if (rule != NULL)
        {
            delete rule;
            rule = NULL;
        }
    }
    m_Rules.clear();
}

FuzzyVariable* FuzzyModule::CreateFLV(const string& VarName)
{
    FuzzyVariable* var = NULL;

    // Comprobamos si existe el nombre
    var =  m_Variables[VarName];
    if (var == NULL)
    {
        var = new FuzzyVariable();
        m_Variables[VarName] = var;
    }
    else
    {
        cerr << "Error(LD CreateFLV): Ya existe una variable con ese nombre" << endl;
        //exit(1);
    }

    return var;
}

void FuzzyModule::AddRule(FuzzyTerm& antecedent, FuzzyTerm& consequence)
{
    m_Rules.push_back(new FuzzyRule(antecedent, consequence));
}


void FuzzyModule::Fuzzify(const string& NameOfFLV, double val)
{
    FuzzyVariable* var = NULL;
    // Comprobamos si existe la variable
    var = m_Variables[NameOfFLV];
    if (var != NULL)
    {
        var->Fuzzify(val);
    }
    else
    {
        cerr << "Error(LD Fuzzify): No existe la variable a fuzzificar" << endl;
        //exit(1);
    }
}

double FuzzyModule::DeFuzzify(const string& NameOfFLV, DefuzzifyType method)
{
    // Comprobamos si existe la variable
    FuzzyVariable* var = NULL;
    var = m_Variables[NameOfFLV];
    if (var != NULL)
    {
        SetConfidencesOfConsequentsToZero();
        vector<FuzzyRule*>::iterator it;
        for (it = m_Rules.begin(); it != m_Rules.end(); it++)
        {
            (*it)->Calculate();
        }

        // En función del método trabajamos
        switch (method)
        {
            case centroid:
                return var->DeFuzzifyCentroid(NumSamplesToUseForCentroid);
            case max_av:
                return var->DeFuzzifyMaxAv();
            default:
                return 0;
        }
    }
    else
    {
        cerr << "Error(LD DeFuzzify): No existe la variable a defuzzificar" << endl;
        //exit(1);
    }

    return 0;
}

void FuzzyModule::SetConfidencesOfConsequentsToZero()
{
    for (int i = 0; i < m_Rules.size(); i++)
    {
        m_Rules[i]->SetConfidenceOfConsequentToZero();
    }
}
