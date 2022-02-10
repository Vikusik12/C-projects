#include <stdio.h>                    
#include <stdlib.h>                    
#include <math.h>
#include <string.h>
                 
#define I0 powl(10,-12)
#define ut 0.0258563
#define cyklus 52 //52 bitu frakce typu double

double funkce(double mid, double u0, double R); //rovnice pro hledani hodnoty napeti Up

double diode(double u0, double R, double eps); //metoda puleni intervalu

int main(int argc, char *argv[]) 
{   
    if (argc != 4)
    {
        fprintf(stderr,"Vstup musi obsahovat prave 4 argumenty\n");
        return 1;
    }
            double u0 = atof(argv[1]);
            double R = atof(argv[2]);
            double eps = atof(argv[3]);
    
    
    
    if (u0 < 0)
    {
        fprintf(stderr,"error: invalid arguments\n"); //Argument nesmi byt zaporny
        return 1;
    }
    
    if(R <=0)
    {
        fprintf(stderr,"error: invalid arguments\n"); //Argument nesmi byt zaporny a jeste nelze rozdelit nulou!
        return 1;
    }
    
    double funkce(double mid, double u0, double R) //popis funkce pro hledani hodnoty napeti Up
    {
        return I0 * exp(mid/ut) - I0 - (u0 - mid)/R;
    }

    
    
    double diode(double u0, double R, double eps)//popis metody puleni intervalu
    {
            double zac = 0;
            double konec = u0;
            double mid;
            int i = 0;  
    
        while(fabs(zac - konec) >= eps)//Ukoncujici podminka 
        {
            mid = (konec - zac)/2; //hodnota delky intervalu
            mid = zac + mid;      //stred intervalu
        
                if (fabs(funkce(zac, u0,R)) < fabs(funkce(mid, u0,R))) // porovnani funkcnich hodnot(se stejnymi znaky), zjisteni zda se v leve casti nachazi blize ke korenu
                    konec = mid;
                else //v opacnem pripade je hledany pristup ke korenu na prave strane
                    zac = mid;
            i++;
            if (i == cyklus)// Aby cyklus byl omezen proti zacykleni pri velmi malem eps
            break;
        }   
        return mid;
    } 
    
    double up = diode (u0, R, eps);
    printf("Up=%g V\n", up);
    
    
    if(argv[1][0]=='i' && argv[1][1]=='n' && argv[1][2]=='f')//
        {
            double Ip = I0 * exp(up/ut) - I0; //pokud Up bude inf, tak urceni proudu v diode podle Shockleyhove rovnici
            printf("Ip=%g A\n", Ip); 
        }
    
    else
        {
            double Ip = (u0 - up)/R; //Urceni proudu v rezistoru podle Kir.zakona
            printf("Ip=%g A\n", Ip); 
        }

    return 0;
}
