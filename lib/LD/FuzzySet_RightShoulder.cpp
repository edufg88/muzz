#include "LD/FuzzySet_RightShoulder.h"
#include "LD/LDAux.h"


/** El conjunto tiene esta forma
             __________
            /
           /
          /
_________/

 */

FuzzySet_RightShoulder::FuzzySet_RightShoulder(double minBound, double peak, double maxBound) :
                        FuzzySet((peak+maxBound)/2.0)
{
    m_dPeakPoint = peak;
    m_dMinBound = minBound;
    m_dMaxBound = maxBound;
}

double FuzzySet_RightShoulder::CalculateDOM(double val)const
{
    double dom = -1;

    if (val > m_dMinBound && val < m_dPeakPoint)
    {
        double den =  m_dPeakPoint - m_dMinBound;

        // Controlamos división por 0
        if (den == 0.0)
        {
            cerr << "ERROR: Division por 0 en RightShoulder" << endl;
            dom = 1;
        }

        dom = (val - m_dMinBound) / den;
    }
    else
    {
        if (val >= m_dPeakPoint)
        {
            dom = 1;
        }
        else
        {
            dom = 0;
        }
    }

    return dom;
}
