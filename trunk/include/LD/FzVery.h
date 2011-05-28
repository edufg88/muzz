#ifndef FZVERY_H
#define FZVERY_H

#include "LD/FuzzyTerm.h"
#include "LD/FuzzySet.h"
#include "LD/FzSet.h"

class FzVery : public FuzzyTerm
{
    public:
        FzVery(FzSet& FzSet);
        ~FzVery();
        FzVery(const FzVery& fzVery);
        FzVery& operator=(const FzVery& fzVery);
        FuzzyTerm* Clone() const;
        double GetDOM() const;
        void ClearDOM();
        void ORwithDOM(double val);
        FuzzySet* GetFuzzySet() const;

    private:
        FuzzySet* fuzzySet;
};

#endif