#include "LD/FzFairly.h"
#include <math.h>

FzFairly::FzFairly(FzSet& fzSet)
{
    fuzzySet = fzSet.GetFuzzySet();
}

FzFairly::~FzFairly()
{
    // Es necesario borrar la memoria?
}

FzFairly::FzFairly(const FzFairly& fzFairly)
{
    *this = fzFairly;
}

FzFairly& FzFairly::operator=(const FzFairly& fzFairly)
{
    if (this != &fzFairly)
        fuzzySet = fzFairly.fuzzySet;

    return *this;
}

FuzzyTerm* FzFairly::Clone() const
{
    return new FzFairly(*this);
}

double FzFairly::GetDOM() const
{
    return (sqrt(fuzzySet->GetDOM()));
}

void FzFairly::ClearDOM()
{
    fuzzySet->ClearDOM();
}

void FzFairly::ORwithDOM(double val)
{
    fuzzySet->ORwithDOM(sqrt(val));
}