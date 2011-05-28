#include "LD/FzSet.h"

FzSet::FzSet(FuzzySet* fs)
{
    fuzzySet = fs;
}

FzSet::~FzSet()
{
    // Es necesario borrar la memoria?
}

FzSet::FzSet(const FzSet& fzSet)
{
    *this = fzSet;
}

FzSet& FzSet::operator=(const FzSet& fzSet)
{
    if (this != &fzSet)
        fuzzySet = fzSet.fuzzySet;

    return *this;
}

FuzzyTerm* FzSet::Clone() const
{
    FzSet* fs = new FzSet(fuzzySet);
    return fs;
}

double FzSet::GetDOM() const
{
    return fuzzySet->GetDOM();
}

void FzSet::ClearDOM()
{
    fuzzySet->ClearDOM();
}

void FzSet::ORwithDOM(double val)
{
    fuzzySet->ORwithDOM(val);
}

FuzzySet* FzSet::GetFuzzySet() const
{
    return fuzzySet;
}