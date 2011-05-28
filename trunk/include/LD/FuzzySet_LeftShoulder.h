#ifndef FUZZY_SET_LEFT_SHOULDER_H
#define FUZZY_SET_LEFT_SHOULDER_H

#include "LD/FuzzySet.h"

class FuzzySet_LeftShoulder : public FuzzySet
{
    public:
        FuzzySet_LeftShoulder(double minBound, double peak, double maxBound);
        double CalculateDOM(double val)const;

    private:
        double m_dPeakPoint;
        double m_dMinBound;
        double m_dMaxBound;
};

#endif