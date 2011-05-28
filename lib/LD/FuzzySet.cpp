#include "LD/FuzzySet.h"

void FuzzySet::ORwithDOM(double val)
{
    // Obtenemos el máximo entre el valor que recibe y el DOM
    if (val > m_dDOM)
        m_dDOM = val;
}

double FuzzySet::GetRepresentativeVal() const
{
    return m_dRepresentativeValue;
}

void FuzzySet::SetDOM(double val)
{
    m_dDOM =  val;
}