#ifndef FZFAIRLY_H
#define FZFAIRLY_H

#include "LD/FuzzyTerm.h"
#include "LD/FuzzySet.h"
#include "LD/FzSet.h"

class FzFairly : public FuzzyTerm
{
    public:
        FzFairly(FzSet& fzSet);
        ~FzFairly();
        FzFairly(const FzFairly& fzFairly);
        FzFairly& operator=(const FzFairly& fzFairly);
        FuzzyTerm* Clone() const;
        double GetDOM() const;
        void ClearDOM();
        void ORwithDOM(double val);

    private:
        FuzzySet* fuzzySet;
};

#endif