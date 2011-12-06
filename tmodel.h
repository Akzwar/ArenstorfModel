#ifndef TMODEL_H
#define TMODEL_H
#include "Matrix.h"
class TModel
{
protected:
    TMatrix* Result;
    double SamplingIncrement;
    double t0;
    double tk;
    TVect* InitConditions;
public:
    TModel(double t0, double tk,TVect* InitConditions);
    TModel(double t0, double tk)
    {
        this->t0=t0;
        this->tk=tk;
    }
    TModel()
    {

    }

    void addResult(TVect* Vect, double t);
    TVect* getInitConditions();
    TMatrix* getResult();
    TVect* getRight(TVect* Vect, double h);
    double getSamplingIncrement();
    double getT0();
    double getTk();
};

class TArenstorfModel : public TModel
{
public:
    TArenstorfModel(double t0, double tk);
    TVect* getRight(TVect* Vect, double h);
};

#endif // TMODEL_H
