#include "LD/FzOr.h"
#include "LD/LDAux.h"

FzOr::FzOr()
{

}

FzOr::FzOr(FuzzyTerm& term1, FuzzyTerm& term2)
{
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
}

FzOr::FzOr(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3)
{
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
    terms.push_back(term3.Clone());
}

FzOr::FzOr(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3, FuzzyTerm& term4)
{
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
    terms.push_back(term3.Clone());
    terms.push_back(term4.Clone());
}

FzOr::~FzOr()
{
    while (terms.size() > 0)
    {
        FuzzyTerm* term = terms.back();
        terms.pop_back();
        if (term != NULL)
        {
            delete term;
            term = NULL;
        }
    }
}

FzOr::FzOr(const FzOr& fzOr)
{
    vector<FuzzyTerm*>::const_iterator it;
    for (it = fzOr.terms.begin(); it !=  fzOr.terms.end(); it++)
    {
        terms.push_back((*it)->Clone());
    }
}

FzOr& FzOr::operator=(const FzOr& fzOr)
{
    if (this != &fzOr)
    {
        while (terms.size() > 0)
        {
            FuzzyTerm* term = terms.back();
            terms.pop_back();
            if (term != NULL)
            {
                delete term;
                term = NULL;
            }
        }

        vector<FuzzyTerm*>::const_iterator it;
        for (it = fzOr.terms.begin(); it != fzOr.terms.end(); it++)
        {
            FuzzyTerm* term = *it;
            terms.push_back(term->Clone());
        }
    }

    return *this;
}

FuzzyTerm* FzOr::Clone() const
{
    return new FzOr(*this);
}

double FzOr::GetDOM() const
{
    double maxDOM = MinDouble;

//     cout << "DOM de FzOR ---- " << endl;

    // Calculamos la unión (OR) devolviendo el máximo DOM
    vector<FuzzyTerm*>::const_iterator it;
    for (it = terms.begin(); it != terms.end(); it++)
    {
        FuzzyTerm* term = *it;

//        cout << "term = " << term->GetDOM() << " max = " << maxDOM << endl;

        if (term->GetDOM() > maxDOM)
        {
            maxDOM = term->GetDOM();
        }
    }

//    cout << "max: " << maxDOM << endl;
//    cout << "-----------------" << endl;

    return maxDOM;
}

void FzOr::ClearDOM() 
{
    // Limpiamos todos los DOM de todos los términos
    vector<FuzzyTerm*>::iterator it;
    for (it = terms.begin(); it != terms.end(); it++)
    {
        FuzzyTerm* term = *it;
        term->ClearDOM();
    }
}

void FzOr::ORwithDOM(double val)
{
    vector<FuzzyTerm*>::iterator it;
    for (it = terms.begin(); it != terms.end(); it++)
    {
        FuzzyTerm* term = *it;
        term->ORwithDOM(val);
    }
}