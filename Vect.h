#ifndef VECT_H
#define VECT_H

#endif // VECT_H
#include <math.h>
class TVect
{
private:
    double *data;
    int Length;
public:
    void setLength(int Length);
    int getLength();
    TVect(int Count);
    TVect(int Count, double *n);
    TVect* operator + (const TVect &Vect)const
    {
        TVect *resultVect;
        resultVect=new TVect(this->Length);
        for(int i=0;i<=this->Length-1;i++)
        resultVect->data[i]=this->data[i]+Vect.data[i];
        return resultVect;
    }

    TVect* operator - (const TVect &Vect)const
    {
        TVect *resultVect;
        resultVect=new TVect(this->Length);
        for(int i=0;i<=this->Length-1;i++)
        resultVect->data[i]=this->data[i]-Vect.data[i];
        return resultVect;
    }

    TVect* operator % (const TVect &cross)const
    {
        if(this->Length==3 && cross.Length==this->Length)
        {
            TVect *tmpVect;
            tmpVect=new TVect(3);
            tmpVect->data[0]=this->data[1]*cross.data[2]-this->data[2]*cross.data[1];
            tmpVect->data[1]=this->data[2]*cross.data[0]-this->data[0]*cross.data[2];
            tmpVect->data[2]=this->data[0]*cross.data[1]-this->data[1]*cross.data[0];
            return tmpVect;
        }
    }

    TVect* operator * (const double cross) const
    {
        TVect *tmpVect;
        tmpVect=new TVect(this->Length);
        for (int i=0;i<=Length-1;i++)
        tmpVect->data[i]=this->data[i]*cross;
        return tmpVect;
    }

    double operator * (const TVect &cross) const
    {
        double tmp;
        tmp=0;
        for (int i=0;i<Length;i++)
        tmp+=this->data[i]*cross.data[i];
        return tmp;
    }

    double getElement(int number);
    double getMagnitude();
    void setElement(int number,double value);
    void addElement(double Value);
};
