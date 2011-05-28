#include "LD/FzAnd.h"
#include "LD/LDAux.h"

FzAnd::FzAnd()
{

}

FzAnd::FzAnd(FuzzyTerm& term1, FuzzyTerm& term2)
{
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
}

FzAnd::FzAnd(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3)
{
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
    terms.push_back(term3.Clone());
}

FzAnd::FzAnd(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3, FuzzyTerm& term4)
{
    terms.push_back(term1.Clone());
    terms.push_back(term2.Clone());
    terms.push_back(term3.Clone());
    terms.push_back(term4.Clone());
}

FzAnd::~FzAnd()
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

FzAnd::FzAnd(const FzAnd& fzAnd)
{
    vector<FuzzyTerm*>::const_iterator it;
    for (it = fzAnd.terms.begin(); it !=  fzAnd.terms.end(); it++)
    {
        terms.push_back((*it)->Clone());
    }
}

FzAnd& FzAnd::operator=(const FzAnd& fzAnd)
{
    if (this != &fzAnd)
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
        for (it = fzAnd.terms.begin(); it != fzAnd.terms.end(); it++)
        {
            FuzzyTerm* term = *it;
            terms.push_back(term->Clone());
        }
    }

    return *this;
}

FuzzyTerm* FzAnd::Clone() const
{
    FzAnd* fzAnd = new FzAnd(*this);
    return fzAnd;
}

double FzAnd::GetDOM() const
{
    double minDOM = MaxDouble;

//    cout << "DOM de FzAND ---- " << endl;

    // Calculamos la intersección (AND) devolviendo el mínimo DOM
    vector<FuzzyTerm*>::const_iterator it;
    for (it = terms.begin(); it != terms.end(); it++)
    {
        FuzzyTerm* term = *it;

//        cout << "term = " << term->GetDOM() << " min = " << minDOM << endl;

        if (term->GetDOM() < minDOM)
        {
            minDOM = term->GetDOM();
        }
    }

//    cout << "min: " << minDOM << endl;
//    cout << "-----------------" << endl;

    return minDOM;
}

void FzAnd::ClearDOM() 
{
    // Limpiamos todos los DOM de todos los términos
    vector<FuzzyTerm*>::iterator it;
    for (it = terms.begin(); it != terms.end(); it++)
    {
        FuzzyTerm* term = *it;
        term->ClearDOM();
    }
}

void FzAnd::ORwithDOM(double val)
{
    vector<FuzzyTerm*>::iterator it;
    for (it = terms.begin(); it != terms.end(); it++)
    {
        FuzzyTerm* term = *it;
        term->ORwithDOM(val);
    }
}