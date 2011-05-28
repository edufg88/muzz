#ifndef FUZZY_SET_TRAPEZIUM_H
#define FUZZY_SET_TRAPEZIUM_H

#include "LD/FuzzySet.h"

class FuzzySet_Trapezium : public FuzzySet
{
    public:
        FuzzySet_Trapezium (double minBound, double peak1, double peak2, double maxBound);
        // Este metodo calcula el grado de pertenencia para un valor dado
        double CalculateDOM(double val)const;

    private:
        // Los valores que representan el triángulo
        double m_dPeakPoint1;
        double m_dPeakPoint2;
        double m_dMinBound;
        double m_dMaxBound;
};


#endif