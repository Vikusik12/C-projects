//Created by Viktoryia Tomason
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>                 
#define I0 powl(10,-12)
#define Ut 0.0258563
//function of finding the voltage by the Shockley equation
double funkce(double mid)
    return I0*exp(mid/Ut);
}
 double diode(double u0, double r, double eps)
 {
    double zac = 0;
    double kon = u0;
    double mid;
    double n_mid=0;
    double Ir;
    //cycle termination condition
    while(fabs(kon-zac)>=eps)
    {
        Ir=(u0-mid)/r;
        //we calculate the value in the middle of the interval;
        mid = (kon-zac)/2;
        mid=mid+zac;
        //anti-cycling
        if(n_mid==mid)
        {break;}
        n_mid=mid;
        // we find out if the root is closer to the beginning
        if(Ir>=funkce(mid))
        zac=mid;
        else
        // we find out if the root is closer to the ending
        kon=mid;
    }
    return mid;
 }
int main(int argc, char *argv[])
{
    if(argc!=4)
    {
        printf("error: invalid arguments\n");
        return 1;
    }

    double u0 = atof(argv[1]);//převod na číslo
        if(u0<=0)
    {
        printf("error: invalid arguments\n");
        return 1;
    }
    double r= atof(argv[2]);//převod na číslo
        if(r<=0)
    {
        printf("error: invalid arguments\n");
        return 1;
    }
 if((argv[1][0]!='i' && argv[1][1]!='n' && argv[1][2]!='f') && (argv[2][0]=='i' && argv[2][1]=='n' && argv[2][2]=='f'))
 {
     		printf("Up=0 V\nIp=0 A\n");
           return 0;
 }
    double eps = atof(argv[3]);
    double Up= diode(u0, r, eps);
    printf("Up=%g V\n",Up);
    double Ipr=I0* exp(Up/Ut)-I0;
    printf("Ip=%g A\n",Ipr);
    return 0; 
}
