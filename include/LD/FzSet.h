#ifndef FZSET_H
#define FZSET_H

#include "LD/FuzzyTerm.h"
#include "LD/FuzzySet.h"

class FzSet : public FuzzyTerm
{
    public:
        FzSet(FuzzySet* fs);
        ~FzSet();
        FzSet(const FzSet& fzSet);
        FzSet& operator=(const FzSet& fzSet);
        FuzzyTerm* Clone() const;
        double GetDOM() const;
        void ClearDOM();
        void ORwithDOM(double val);
        FuzzySet* GetFuzzySet() const;

    private:
        FuzzySet* fuzzySet;
};

#endif