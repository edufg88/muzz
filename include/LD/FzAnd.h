#ifndef FZAND_H
#define FZAND_H

#include "LD/FuzzyTerm.h"
#include "LD/FuzzySet.h"
#include <vector>
using namespace std;

class FzAnd : public FuzzyTerm
{
    public:
        FzAnd();
        FzAnd(FuzzyTerm& term1, FuzzyTerm& term2);
        FzAnd(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3);
        FzAnd(FuzzyTerm& term1, FuzzyTerm& term2, FuzzyTerm& term3, FuzzyTerm& term4);
        ~FzAnd();
        FzAnd(const FzAnd& fzAnd);
        FzAnd& operator=(const FzAnd& fzAnd);
        FuzzyTerm* Clone() const;
        double GetDOM() const;
        void ClearDOM();
        void ORwithDOM(double val);

    private:
        // Vector con los términos difusos que forman parte del FzAnd
        vector<FuzzyTerm*> terms;
};

#endif