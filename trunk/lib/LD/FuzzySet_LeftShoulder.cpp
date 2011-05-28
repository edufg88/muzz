#include "LD/FuzzySet_LeftShoulder.h"
#include "LD/FuzzySet.h"
#include "LD/LDAux.h"
#include <iostream>
using namespace std;

/** El conjunto tiene esta forma
 _________
          \
           \
            \
             \________
 */

FuzzySet_LeftShoulder::FuzzySet_LeftShoulder(double minBound, double peak, double maxBound) : FuzzySet((minBound+peak)/2.0)
{
    m_dMinBound = minBound;
    m_dMaxBound = maxBound;
    m_dPeakPoint = peak;
}

double FuzzySet_LeftShoulder::CalculateDOM(double val) const
{
    double dom = -1;

    if (val > m_dPeakPoint && val < m_dMaxBound)
    {
        double den = m_dMaxBound - m_dPeakPoint;

        if(den == 0.0)
        {
            cerr << "ERROR: division por 0 en LeftShoulder" << endl;
            dom = 1;
        }

        dom = (m_dMaxBound - val)/den;
    }
    else
    {
        if (val <= m_dPeakPoint)
            dom = 1;
        else
        {
            dom = 0;
        }
    }

    return dom;
}