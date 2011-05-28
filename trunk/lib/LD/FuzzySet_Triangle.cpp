#include "LD/FuzzySet_Triangle.h"
#include "LD/LDAux.h"

/** El conjunto tiene esta forma
 *
      /\
     /  \
    /    \
   /      \
__/        \__

 */

double FuzzySet_Triangle::CalculateDOM(double val) const
{
    double dom = -1;

    if (val > m_dMinBound && val <= m_dPeakPoint)
    {
        double den = m_dPeakPoint - m_dMinBound;

        if (den == 0.0)
        {
            cerr << "ERROR: division por 0 en Triangle" << endl;
            dom = 1;
        }

        dom = (val - m_dMinBound) / den;
    }
    else
    {
        if (val > m_dPeakPoint && val < m_dMaxBound)
        {
            double den = m_dMaxBound - m_dPeakPoint;

            if (den == 0.0)
            {
                cerr << "ERROR: division por 0 en Triangle" << endl;
                dom = 1;
            }

            dom = (m_dMaxBound - val) / den;
        }
        else
        {
            dom = 0;
        }
    }

    return dom;
}

