#ifndef MATRIX_H
#define MATRIX_H
#endif // MATRIX_H
#include "Vect.h"
class TMatrix
{
private:
    double **data;
    int Height;
    int Width;
public:
    int getHeight()const;
    int getWidth()const;
    TMatrix(int Width, int Height, double *n);
    TMatrix(int Width, int Height);
    ~TMatrix();
    TMatrix* operator * (const double lambda)const
    {
        double *n;
        n=new double[Width*Height];
        for(int i=0;i<Width;i++)
            for(int j=0;j<Height;j++)
            n[i*Height+j]=lambda*data[i][j];
        TMatrix *resultMatrix;
        resultMatrix=new TMatrix(this->Width,this->Height,n);
        delete [] n;
        return resultMatrix;
    }
    TMatrix* operator + (const TMatrix &Matr)const
    {
        if (this->Height==Matr.getHeight()
                &&this->Width==Matr.getWidth())
        {
            double *n;
            n=new double[Width*Height];
            for(int i=0;i<Width;i++)
                for(int j=0;j<Height;j++)
                    n[i*Height+j]=this->data[i][j]+Matr.data[i][j];
            TMatrix *resultMatrix;
            resultMatrix=new TMatrix(this->Width,this->Height,n);
            delete [] n;
            return resultMatrix;
        }
    }
    TMatrix* operator *(const TMatrix &Matr)const
    {
        if(this->Width==Matr.Height)
        {
            double *n;
            TVect *Vect1;
            TVect *Vect2;
            n=new double[Matr.Width*this->Height];
            for(int i=0;i<Matr.Width;i++)
            {
                Vect1=new TVect(Matr.Height);
                for(int k=0; k<Matr.Height; k++)
                    Vect1->setElement(k,Matr.data[i][k]);
                for(int j=0;j<this->Height;j++)
                    {
                        Vect2=new TVect(this->Width);
                        for(int k=0; k<this->Width; k++)
                            Vect2->setElement(k,this->data[k][j]);
                        n[i*this->Height+j]=*Vect1 * *Vect2;
                        delete Vect2;
                    }
                delete Vect1;
            }
            TMatrix *ResultMatrix=new TMatrix(Matr.Width,this->Height,n);
            delete [] n;
            return ResultMatrix;
         }
     }
    TMatrix* Inverse();
    void RowReverse(int a, int b);
    void ColReverse(int a, int b);
    double getElement(int Width, int Height);
    void setElement(int Width, int Height, double Value);
    void setColumn(int Column, TVect* Vect);
    void setRow(int Row, TVect* Vect);
    TVect* getColumn(int Column);
    TVect* getRow(int Row);
    void addColumn(TVect* Vect);
    void addRow(TVect* Vect);
    void RemoveColumn(int Column);
    void RemoveRow(int Row);
};
