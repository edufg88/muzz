#ifndef FUZZY_SET_TRIANGLE_H
#define FUZZY_SET_TRIANGLE_H

#include "LD/FuzzySet.h"

class FuzzySet_Triangle : public FuzzySet
{
    public:
        FuzzySet_Triangle(double minBound, double peak, double maxBound) :
                          FuzzySet(peak), m_dMinBound(minBound), m_dMaxBound(maxBound), m_dPeakPoint(peak)
        {
        }
        // Este metodo calcula el grado de pertenencia para un valor dado
        double CalculateDOM(double val)const;

    private:
        // Los valores que representan el triángulo
        double m_dPeakPoint;
        double m_dMinBound;
        double m_dMaxBound;
};


#endif