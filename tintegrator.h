#ifndef TINTEGRATOR_H
#define TINTEGRATOR_H
#include "tmodel.h"
class TIntegrator
{
protected:
    double eps;
public:
    TIntegrator();
    void Run(TModel Model);
};

class TDormandPrinceIntegrator : public TIntegrator
{
private:
    double a[8][7];
    double b[7];
    double b1[7];
    double c[7];
public:
    TDormandPrinceIntegrator();
    void Run(TModel Model);
};

#endif // TINTEGRATOR_H
