#include "tmodel.h"
#include <math.h>
#include <Vect.h>
TModel::TModel(double t0, double tk, TVect *InitConditions)
{
    this->Result = new TMatrix(InitConditions->getLength()+1,1);
    this->t0=t0;
    this->tk=tk;
    this->InitConditions=InitConditions;
}

TModel::addResult(const TVect *Vect, double t)
{
    Vect->addElement(t);
    Result->addRow(Vect);
}

TVect* TModel::getInitConditions()
{
    return this->InitConditions;
}

TMatrix* TModel::getResult()
{
    return this->Result;
}

double TModel::getSamplingIncrement()
{
    return this->SamplingIncrement;
}

double TModel::getT0()
{
    return this->t0;
}

double TModel::getTk()
{
    return this->tk;
}

TArenstorfModel::TArenstorfModel(double t0, double tk)
{
    this->t0=t0;
    this->tk=tk;
    double n=new double[6];
    n[0]=0.994;
    n[1]=0;
    n[2]=0;
    n[3]=-2.00158510637908252240537862224;
    double D1=pow(pow(n[0]+this->mu,2)+pow(n[1],2),3/2);
    double D2=pow(pow(n[0]-(1-this->mu),2)+pow(n[1],2),3/2);
    n[4]=n[0]+2*n[3]-(mu*((n[0]+mu)/D1)-mu*((n[0]-(1-mu))/D2));
    n[5]=n[1]-2*n[2]-((1-mu)*((n[1])/D1)-mu*((n[1])/D2));
    InitConditions=new TVect(6,n);
    delete [] n;
    this->Result = new TMatrix(InitConditions->getLength()+1,1);
}

TVect* TArenstorfModel::getRight(TVect *Vect, double h)
{
    TVect* resultVect=new TVect(6);
    resultVect->setElement(0,Vect->getElement(0)+Vect->getElement(2)*h);
    resultVect->setElement(1,Vect->getElement(1)+Vect->getElement(3)*h);
    resultVect->setElement(2,Vect->getElement(2)+Vect->getElement(4)*h);
    resultVect->setElement(3,Vect->getElement(3)+Vect->getElement(5)*h);
    resultVect->setElement(4,Vect->getElement(0)+2*Vect->getElement(3)-(mu*((Vect->getElement(0)+mu)/D1)-mu*((Vect->getElement(0)-(1-mu))/D2)));
    resultVect->setElement(5,Vect->getElement(1)-2*Vect->getElement(2)-((1-mu)*((Vect->getElement(1))/D1)-mu*((Vect->getElement(1))/D2)));
    return resultVect;
}
