#ifndef FUZZY_SET_H
#define FUZZY_SET_H
#include <iostream>
using namespace std;
class FuzzySet
{
    public:
        FuzzySet(double RepVal):m_dDOM(0.0), m_dRepresentativeValue(RepVal){}
        // Devuelve el grado de pertenencia in este conjunto de un valor dado.
        // pero no lo almacena en m_dDOM
        virtual double CalculateDOM(double val)const = 0;
        //if this fuzzy set is part of a consequent FLV and it is fired by a rule,
        //then this method sets the DOM (in this context, the DOM represents a
        //confidence level) to the maximum of the parameter value or the set's
        //existing m_dDOM value
        void ORwithDOM(double val);
        
        double GetRepresentativeVal()const;
        void ClearDOM(){m_dDOM = 0.0;}
        double GetDOM()const
        {
            //cout << "FuzzySet DOM: " << m_dDOM << endl;
            return m_dDOM;
        }
        void SetDOM(double val);

    protected:
        // Grado de pertenencia en este conjunto de un valor dado
        double m_dDOM;
        double m_dRepresentativeValue;
};

#endif