#ifndef FUZZY_SET_RIGHT_SHOULDER_H
#define FUZZY_SET_RIGHT_SHOULDER_H

#include "LD/FuzzySet.h"

class FuzzySet_RightShoulder : public FuzzySet
{
    public:
        FuzzySet_RightShoulder(double minBound, double peak, double maxBound);
        double CalculateDOM(double val)const;

    private:
        double m_dPeakPoint;
        double m_dMinBound;
        double m_dMaxBound;
};



#endif