#include <Vect.h>

TVect::TVect(int Count)
{
    data=new double[Count];
    for(int i=0;i<Count;i++)
        data[i]=0;
    Length=Count;
}

TVect::TVect(int Count, double *n)
{
    data=new double [Count];
    for(int i=0;i<Count;i++)
        data[i]=n[i];
    Length=Count;
}

void TVect::setLength(int newcount)
{
    delete [] data;
    data=new double[newcount];
    Length=newcount;
}

int TVect::getLength()
{
    return Length;
}

void TVect::setElement(int number,double value)
{
   this->data[number]=value;
}

void TVect::addElement(double Value)
{
    this->setLength(this->getLength()+1);
    this->setElement(this->Length-1,Value);
}

double TVect::getElement(int number)
{
  return data[number];
}

double TVect::getMagnitude()
{
    double s;
    s=0;
    for(int i=0;i<=Length-1;i++)
    s=s+pow(data[i],2);
    return sqrt(s);
}
