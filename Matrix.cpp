#include <Matrix.h>
#include <stdarg.h>
#include <QDebug>
TMatrix::TMatrix(int Width, int Height, double *n)//Параметр n- указатель
{                                                 //на одномерный динамический массив
    data= new double*[Width];                     //Из него созается двумерный массив,
    for(int i=0;i<Width;i++)                      //который заполняется по столбцам, т.е.:
    {                                             //|n[1] n[4] n[7]| |data[1][1] data[2][1] data[3][1]|
        data[i]= new double[Height];              //|n[2] n[5] n[8]|=|data[1][2] data[2][2] data[3][2]|
        for(int j=0;j<Height;j++)                 //|n[3] n[6] n[9]| |data[1][3] data[2][3] data[3][3]|
        {
            data[i][j]=n[i*Height+j];
        }
    }
    this->Height=Height;
    this->Width=Width;
}

TMatrix::TMatrix(int Width, int Height)
{
    data= new double*[Width];
    for(int i=0;i<Width;i++)
    {
        data[i]= new double[Height];
        for(int j=0;j<Height;j++)
        {
            data[i][j]=0;
        }
    }
    this->Height=Height;
    this->Width=Width;

}

TMatrix::~TMatrix()
{
    for(int i=0;i<=Width-1;i++)
        delete data[i];
}

int TMatrix::getHeight()const
{
    return this->Height;
}

int TMatrix::getWidth()const
{
    return this->Width;
}

void TMatrix::setElement(int Width, int Height, double Value)
{
    this->data[Width][Height]=Value;
}

double TMatrix::getElement(int Width, int Height)
{
  return data[Width][Height];
}

void TMatrix::addColumn(TVect *Vect)
{
    double **olddata=data;
    data= new double*[this->Width+1];
    for(int i=0;i<this->Width+1;i++)
    {
        data[i]= new double[this->Height];
        for(int j=0;j<this->Height;j++)
        {
            if(i!=this->Width)
                data[i][j]=olddata[i][j];
            else
                data[i][j]=Vect->getElement(j);
        }
    }
    this->Width++;

}

void TMatrix::addRow(TVect *Vect)
{
    double **olddata=data;
    data= new double*[this->Width];
    for(int i=0;i<this->Width;i++)
    {
        data[i]= new double[this->Height+1];
        for(int j=0;j<this->Height+1;j++)
        {
            if(i!=Height)
                data[i][j]=olddata[i][j];
            else
                data[i][j]=Vect->getElement(i);
        }
    }
    this->Height++;

}

TVect* TMatrix::getColumn(int Column)
{
    TVect* ResultVect=new TVect(this->getHeight());
    for(int i=0;i<this->getHeight();i++)
        ResultVect->setElement(i,this->getElement(Column,i));
    return ResultVect;
}

TVect* TMatrix::getRow(int Row)
{
    TVect* ResultVect=new TVect(this->getWidth());
    for(int i=0;i<this->getWidth();i++)
        ResultVect->setElement(i,this->getElement(i,Row));
    return ResultVect;
}

void TMatrix::setColumn(int Column, TVect *Vect)
{
    for(int i=0;i<this->getHeight();i++)
        this->setElement(Column, i, Vect->getElement(i));
}

void TMatrix::setRow(int Row, TVect *Vect)
{
    for(int i=0;i<this->getWidth();i++)
        this->setElement(i, Row, Vect->getElement(i));
}

void TMatrix::ColReverse(int a, int b)
{
    TVect* TempVect=this->getColumn(a);
    this->setColumn(a,this->getColumn(b));
    this->setColumn(b,TempVect);
}

void TMatrix::RowReverse(int a, int b)
{
    TVect* TempVect=this->getRow(a);
    this->setRow(a,this->getRow(b));
    this->setRow(b,TempVect);
}

void TMatrix::RemoveColumn(int Column)
{
    double **olddata=data;
    data= new double*[this->Width-1];
    for(int i=0;i<Column;i++)
    {
        data[i]= new double[this->Height];
        for(int j=0;j<this->Height;j++)
        {
            data[i][j]=olddata[i][j];
        }
    }
    for(int i=Column+1;i<this->getWidth();i++)
    {
        data[i-1]= new double[this->Height];
        for(int j=0;j<this->Height;j++)
        {
            data[i-1][j]=olddata[i][j];
        }
    }
    this->Width--;
}
void TMatrix::RemoveRow(int Row)
{
    double **olddata=data;
    data= new double*[this->Width];
    for(int i=0;i<this->Width;i++)
    {
        data[i]= new double[this->Height-1];
        for(int j=0;j<Row;j++)
        {
            data[i][j]=olddata[i][j];
        }
        for(int j=Row+1;j<this->getHeight();j++)
        {
            data[i][j-1]=olddata[i][j];
        }
    }
    this->Height--;
}

TMatrix* TMatrix::Inverse()
{
    bool Simmetr=false;
    for(int i=0;i<this->getHeight();i++)
        for(int j=0;j<this->getHeight();j++)
        {
            if(this->data[i][j]!=this->data[j][i])
                Simmetr=false;
        }
    TMatrix* ResultMatr;

    ResultMatr=new TMatrix(this->getWidth(),this->getHeight());
   // if(Simmetr=false)
    //{
        TVect* CurrColumn=NULL;
        ResultMatr->data=this->data;
        double *n=new double[this->Width];
        for(int i=0; i<this->Width; i++)
        {
            for(int j=0; j<this->Height; j++)
                if(i==j)
                    n[j]=1;
                else
                    n[j]=0;
            ResultMatr->addColumn(new TVect(this->Height,n));
        }
        for(int i=0; i<ResultMatr->getHeight();i++)
        {
            fprintf(stderr, "\n");
            for(int j=0;j<ResultMatr->getWidth();j++)
                fprintf(stderr,"% 6.2f ",ResultMatr->getElement(j,i));
        }
        fprintf(stderr, "\n");
        //////////Получение верхней треугольной матрицы

        for(int k=0;k<this->getHeight();k++)
        {
            int i=0;
            int j=k;
            bool b=false;
            while(i<this->getWidth() && b==false)
            {
                while(b==false && j<this->getHeight())
                {
                    if(ResultMatr->data[i][j]!=0)
                    {
                        CurrColumn=ResultMatr->getColumn(i);
                        b=true;
                    }
                        j++;
                }
                i++;
                j=k;
            }
            if(CurrColumn->getElement(k)==0)
            {
                for(int i=1;i<this->getWidth();i++)
                    if(CurrColumn->getElement(i)!=0)
                    {
                        ResultMatr->RowReverse(k,i);
                        CurrColumn=ResultMatr->getRow(k);
                        break;
                    }
            }
            ResultMatr->setRow(k,*(ResultMatr->getRow(k))*(1/CurrColumn->getElement(k)));
            for(int i=k+1;i<this->getHeight();i++)
                ResultMatr->setRow(i,
                *(ResultMatr->getRow(i))-*(*(ResultMatr->getRow(k))*ResultMatr->getRow(i)->getElement(k)));
            for(int i=0; i<ResultMatr->getHeight();i++)
            {
                fprintf(stderr, "\n");
                for(int j=0;j<ResultMatr->getWidth();j++)
                    fprintf(stderr,"% 6.2f ",ResultMatr->getElement(j,i));
            }
            fprintf(stderr, "\n");
        }
        for(int k=2;k<=this->getHeight();k++)
        {
            for(int i=this->getHeight()-k;i>=0;i--)
            ResultMatr->setRow(i,
            *(ResultMatr->getRow(i))-*(*(ResultMatr->getRow(this->getHeight()-k+1))*ResultMatr->getRow(i)->getElement(this->getWidth()-k+1)));
        }
       for(int i=0; i<ResultMatr->getHeight();i++)
        {
            fprintf(stderr, "\n");

            for(int j=0;j<ResultMatr->getWidth();j++)
                fprintf(stderr,"% 6.2f ",ResultMatr->getElement(j,i));
        }
        fprintf(stderr, "\n");
        for(int i=0;i<this->Height;i++)
        ResultMatr->RemoveColumn(0);
  //  }
//    else
//    {
//        double buff;
//        for(int i=0;i<this->getHeight();i++)
//        {
//            for(int j=0;j<i;j++)
//            {
//                buff=this->data[i][j];
//                for(int k=0;k<j;k++)
//            }
//        }
//    }
    return ResultMatr;
}


