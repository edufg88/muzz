#include "LD/FuzzySet_Trapezium.h"
#include <iostream>
using namespace std;

/** El conjunto tiene esta forma
 *     ____________
      /            \
     /              \
    /                \
   /                  \
__/                    \__

 */

FuzzySet_Trapezium::FuzzySet_Trapezium (double minBound, double peak1, double peak2, double maxBound) : FuzzySet((peak1+peak2) / 2.0)
{
    m_dMinBound = minBound;
    m_dPeakPoint1 = peak1;
    m_dPeakPoint2 = peak2;
    m_dMaxBound = maxBound;
}

double FuzzySet_Trapezium::CalculateDOM(double val) const
{
    double dom = -1;

    if (val > m_dMinBound && val <= m_dPeakPoint1)
    {
        double den = m_dPeakPoint1 - m_dMinBound;

        if (den == 0)
        {
            cerr << "ERROR: division por 0 en Trapezium" <<endl;
            dom = 1;
        }

        dom = (val - m_dMinBound) / den;
    }
    else if (val > m_dPeakPoint1 && val < m_dPeakPoint2)
    {
        dom = 1;
    }
    else if (val >= m_dPeakPoint2 && val < m_dMaxBound)
    {
        double den = m_dMaxBound - m_dPeakPoint2;

        if (den == 0)
        {
            cerr << "ERROR: division por 0 en Trapezium" << endl;
            dom = 1;
        }

        dom = (m_dMaxBound - val) / den;
    }
    else
    {
        dom = 0;
    }

    return dom;
}