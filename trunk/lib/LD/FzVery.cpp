#include "LD/FzVery.h"
#include <math.h>

FzVery::FzVery(FzSet& fzSet)
{
    fuzzySet = fzSet.GetFuzzySet();
}

FzVery::~FzVery()
{
    // Es necesario borrar la memoria?
}

FzVery::FzVery(const FzVery& fzVery)
{
    *this = fzVery;
}

FzVery& FzVery::operator=(const FzVery& fzVery)
{
    if (this != &fzVery)
        fuzzySet = fzVery.fuzzySet;

    return *this;
}

FuzzyTerm* FzVery::Clone() const
{
    return new FzVery(*this);
}

double FzVery::GetDOM() const
{
    return ((fuzzySet->GetDOM())*(fuzzySet->GetDOM()));
}

void FzVery::ClearDOM()
{
    fuzzySet->ClearDOM();
}

void FzVery::ORwithDOM(double val)
{
    fuzzySet->ORwithDOM(val*val);
}