#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>                 
#define I0 powl(10,-12)
#define Ut 0.0258563
double funkce(double mid)//funkce nalezení napětí podle Shockleyove rovnice
{
    return I0*exp(mid/Ut);
}
 double diode(double u0, double r, double eps)
 {
    double zac = 0;
    double kon = u0;
    double mid;
    double n_mid=0;
    double Ir;
    while(fabs(kon-zac)>=eps)//podmínka ukončení cyklu
    {
        Ir=(u0-mid)/r;
        mid = (kon-zac)/2;// vypočítáme hodnotu ve středu intervalu;
        mid=mid+zac;
        if(n_mid==mid)//osetreni proti zacyklovani
        {break;}
        n_mid=mid;
        if(Ir>=funkce(mid))//zjistujeme, zda se nachází kořen blíže ke zacatku
        zac=mid;
        else//v opačném případě je hledaný přístup ke kořenu bliz ke konci
        kon=mid;
    }
    return mid;
 }
int main(int argc, char *argv[])
{//kontrola argumentu
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
