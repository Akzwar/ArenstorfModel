#ifndef TMODEL_H
#define TMODEL_H
#include <Matrix.h>
class TModel
{
private:
    TMatrix* Result;
    double SamplingIncrement;
    double t0;
    double tk;
    TVect* InitConditions;
public:
    TModel(double t0, double tk,TVect* InitConditions);
    void addResult(const TVect* Vect, double t);
    TVect* getInitConditions();
    TMatrix* getResult();
    virtual TVect* getRight(TVect* Vect, double h);
    double getSamplingIncrement();
    double getT0();
    double getTk();
};

class TArenstorfModel : public TModel
{
private:
    const double mu=0.012277471;
public:
    TArenstorfModel(double t0, double tk);
    TVect* getRight(TVect* Vect, double h);
};

#endif // TMODEL_H
