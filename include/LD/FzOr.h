#ifndef FZOR_H
#define FZOR_H

#include "LD/FuzzyTerm.h"
#include "LD/FuzzySet.h"
#include <vector>
using namespace std;

class FzOr: public FuzzyTerm
{
    public:
        FzOr();
        FzOr(FuzzyTerm& term1, FuzzyTerm& term2);
        FzOr(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3);
        FzOr(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3, FuzzyTerm& term4);
        ~FzOr();
        FzOr(const FzOr& fzOr);
        FzOr& operator=(const FzOr& fzOr);
        FuzzyTerm* Clone() const;
        double GetDOM() const;
        void ClearDOM() ;
        void ORwithDOM(double val);

    private:
        // Vector con los términos difusos que forman parte del FzOr
        vector<FuzzyTerm*> terms;
};

#endif