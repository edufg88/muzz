#include <map>

#include "LD/FuzzyVariable.h"
#include "LD/FuzzySet_Triangle.h"
#include "LD/FuzzySet_RightShoulder.h"
#include "LD/FuzzySet_LeftShoulder.h"
#include "LD/FuzzySet_Trapezium.h"
#include "LD/LDAux.h"

FuzzyVariable::~FuzzyVariable()
{
    MemberSets::iterator it;
    for (it = m_MemberSets.begin(); it != m_MemberSets.end(); it++)
    {
        FuzzySet* set = (*it).second;
        m_MemberSets.erase(it);
        if (set != NULL)
        {
            delete set;
            set = NULL;
        }
    }
}

FzSet FuzzyVariable::AddTriangularSet(string name, double minBound, double peak, double maxBound)
{
    // Creamos el conjunto
    FuzzySet* set = new FuzzySet_Triangle(minBound, peak, maxBound);
    // Añadimos el conjunto a la lista de conjuntos miembro
    m_MemberSets[name] = set;
    // Recalculamos el rango del conjunto
    AdjustRangeToFit(minBound, maxBound);

    // Devolvemos el conjunto a traves de su clase proxy
    return (FzSet(set));
}

FzSet FuzzyVariable::AddRightShoulderSet(string name, double minBound, double peak, double maxBound)
{
    FuzzySet* set = new FuzzySet_RightShoulder(minBound, peak, maxBound);
    m_MemberSets[name] = set;
    AdjustRangeToFit(minBound, maxBound);

    return (FzSet(set));
}

FzSet FuzzyVariable::AddLeftShoulderSet(string name, double minBound, double peak, double maxBound)
{
    FuzzySet* set = new FuzzySet_LeftShoulder(minBound, peak, maxBound);
    m_MemberSets[name] = set;
    AdjustRangeToFit(minBound, maxBound);

    return (FzSet(set));
}

FzSet FuzzyVariable::AddTrapeziumSet(string name, double minBound, double peak1, double peak2, double maxBound)
{
    FuzzySet* set = new FuzzySet_Trapezium(minBound, peak1, peak2, maxBound);
    m_MemberSets[name] = set;
    AdjustRangeToFit(minBound, maxBound);

    return (FzSet(set));
}

void FuzzyVariable::AdjustRangeToFit(double min, double max)
{
    if (min < m_dMinRange)
    {
        m_dMinRange = min;
    }
    if (max > m_dMaxRange)
    {
        m_dMaxRange = max;
    }
}

void FuzzyVariable::Fuzzify(double val)
{
    // Comprobamos que el valor este dentro de los rangos
    if (val < m_dMinRange)
        val = m_dMinRange;
    if (val > m_dMaxRange)
        val = m_dMaxRange;

    //cout << "Fuzzify (" << val << ")...................." << endl;

    MemberSets::iterator it;
    for (it = m_MemberSets.begin(); it !=  m_MemberSets.end(); it++)
    {
        // Calculamos el DOM
        double DOM = (*it).second->CalculateDOM(val);
        // Y lo almacenamos
        (*it).second->SetDOM(DOM);

        //cout << "Conjunto: " << (*it).first << endl;
        //cout << "Dom: " << (*it).second->GetDOM() << endl;
    }

    //cout << ".........................." << endl;
}

double FuzzyVariable::DeFuzzifyMaxAv() const
{
    double num = 0.0;
    double den = 0.0;

    //cout << "DefuzzifyMaxAv: ......" << endl;

    MemberSets::const_iterator it;
    for (it = m_MemberSets.begin(); it != m_MemberSets.end(); it++)
    {
        den += (*it).second->GetDOM();
        num += (*it).second->GetRepresentativeVal() * (*it).second->GetDOM();

//        cout << "Conjunto: " << (*it).first << endl;
//        cout << "Dom: " << (*it).second->GetDOM() << endl;
//        cout << "RepVal: " << (*it).second->GetRepresentativeVal() << endl << endl;
    }

    // Corregimos el valor del denominador (no puede ser 0)
    if (isEqual(den, 0.0))
        return 0.0;

    /*
     * En el num tenemos: Sum(valorRep * confianza)
     * En el den tenemos: Sum(confianza)
     * Devolvemos el cociente que sera el valor concreto defuzzificado
     */

//    cout << "......................." << endl;
    return (num / den);
}

double FuzzyVariable::DeFuzzifyCentroid(int NumSamples) const
{
    // El paso será la distancia entre cada una de las partes que cogemos de muestra
    double paso = (m_dMaxRange - m_dMinRange) / (double)NumSamples;
    double areaTotal = 0.0;
    double sumDeMomentos = 0.0;

//    cout << "DefuzzifyCentroid: ......" << endl;
//    cout << "Samples: " << NumSamples << endl;

    for (int sample = 1; sample <= NumSamples; sample++)
    {
        MemberSets::const_iterator it;
        for(it = m_MemberSets.begin(); it != m_MemberSets.end(); it++)
        {
            FuzzySet* set = (*it).second;
            double contribution = minimum(set->CalculateDOM(m_dMinRange + sample * paso), set->GetDOM());
            areaTotal += contribution;
            sumDeMomentos += (m_dMinRange + sample * paso) * contribution;
            
//            cout << "SET: " << (*it).first << " , DOM: " << (*it).second->GetDOM() << endl;
        }
    }

    // Vigilamos que el denominador no sea 0
    if (isEqual(areaTotal, 0.0))
    {
        return 0.0;
    }

//    cout << "....................." << endl;
    /*
     * En sumDeMomentos almacenamos: Sum(s*Dom(s))
     * En areaTotal almacenamos: Sum(Dom(s))
     * 's' es el valor de la función para cada una de las partes de muestra
     * Dom(s) es el DOM de la variable difusa en ese punto
     */
    return (sumDeMomentos / areaTotal);
}

