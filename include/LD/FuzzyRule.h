#ifndef FUZZY_RULE_H
#define FUZZY_RULE_H

#include "LD/FuzzyTerm.h"
#include <iostream>
using namespace std;

class FuzzyRule
{
    public:
        FuzzyRule(FuzzyTerm& ant, FuzzyTerm& con):m_pAntecedent(ant.Clone()), m_pConsequence(con.Clone())
        {

        }

        ~FuzzyRule()
        {
            if (m_pAntecedent != NULL)
                delete m_pAntecedent;
            if (m_pConsequence != NULL)
                delete m_pConsequence;
        }

        void SetConfidenceOfConsequentToZero()
        {
            m_pConsequence->ClearDOM();
        }

        // Este método actualiza el DOM del consecuente con el DOM del antecedente
        void Calculate()
        {
//            cout << "Rule Calculate ####### " << endl;

            m_pConsequence->ORwithDOM(m_pAntecedent->GetDOM());

//            cout << "Ant DOM: " << m_pAntecedent->GetDOM() << " Cons DOM: " << m_pConsequence->GetDOM() << endl;
//            cout << "------------------- ######" << endl;

        }

    private:
        const FuzzyTerm* m_pAntecedent;
        FuzzyTerm* m_pConsequence;
        // No permitimos copia ni asignación
        FuzzyRule(const FuzzyRule&);
        FuzzyRule& operator=(const FuzzyRule&);
};


#endif