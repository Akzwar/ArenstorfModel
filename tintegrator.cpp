#include "tintegrator.h"

TIntegrator::TIntegrator()
{
}

TDormandPrinceIntegrator::TDormandPrinceIntegrator():TIntegrator()
{
    eps=1e-8;
    a[2][1]=1/5;
    a[3][1]=3/40;
    a[3][2]=9/40;
    a[4][1]=44/45;
    a[4][2]=-56/15;
    a[5][3]=32/9;
    a[5][1]=19372/6561;
    a[5][2]=-25360/2187;
    a[5][3]=64448/6561;
    a[5][4]=-212/729;
    a[6][1]=9017/3168;
    a[6][2]=-355/33;
    a[6][3]=46372/5247;
    a[6][4]=49/176;
    a[6][5]=-5103/18656;
    a[7][1]=35/384;
    a[7][2]=0;
    a[7][3]=500/1113;
    a[7][4]=125/192;
    a[7][5]=-2187/6784;
    a[7][6]=11/84;
    b[1]=35/384;
    b[2]=0;
    b[3]=500/1113;
    b[4]=125/192;
    b[5]=-2187/6748;
    b[6]=11/84;
    b[7]=0;
    b1[1]=5079/57600;
    b1[2]=0;
    b1[3]=7571/16695;
    b1[4]=393/640;
    b1[5]=-92097/339200;
    b1[6]=187/2100;
    b1[7]=1/40;
    c[2]=1/5;
    c[3]=3/10;
    c[4]=4/5;
    c[5]=8/9;
    c[6]=1;
    c[7]=1;
}

void TDormandPrinceIntegrator::Run(TModel Model)
{
    TVect* tmpVect[7];
    TVect* resVect;
    TVect* incr=new TVect(Model.getInitConditions()->getLength());
    resVect=Model.getInitConditions();
    for(int i=1;i<=5;i++)
        tmpVect[i]=new TVect(Model.getInitConditions()->getLength());
    double h=0.5;
    for(int i=Model.getT0();i<=Model.getTk();i+=h)
    {
        tmpVect[0]=Model.getRight(resVect,i);
        for(int j=1;j<=5;j++)
        {
            incr= new TVect(Model.getInitConditions()->getLength());
            for(int k=1;k<=j-1;k++)
                incr=*incr+(*tmpVect[k]*a[j][k]);
            tmpVect[i]=Model.getRight(*resVect+(*incr*h),i+c[j]*h);
            incr=0;
            for(int k=1;k<=j-1;k++)
                incr=*incr+(*tmpVect[k]*b[k]);
            resVect=*resVect+*incr*h;
        }
    }

}
