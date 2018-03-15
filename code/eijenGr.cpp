#include<vector>
#include<cstdio>
#include<Interval.h>
using namespace std;

/*Eijgenraam's method for the system y1'=y2, y2'=y1*/

/*Notations : 
yiTight = enclosure des valeurs de y a tj -> [yi] du papier
yiLarge = enclosure des valeurs de y entre tj et tj+1 -> [yi~] du papier*/


REAL F[2][2];

void f(INTERVAL *x, INTERVAL* y){
    y[0] = x[1];
    y[1] = x[0];
}

REAL step1SimpleMethod(INTERVAL* oldYtight, REAL maxH, REAL alpha, INTERVAL* newYLarge){
    INTERVAL temp[2];
    REAL h = maxH;
    INTERVAL hInter(0, h);
    INTERVAL alphaINter(-alpha, alpha);
    INTERVAL oldYLarge[2];
    oldYLarge[0] = oldYtight[0];
    oldYLarge[1] = oldYtight[1];
    f(oldYtight, temp);
    newYLarge[0] = oldYLarge[0] + hInter * temp[0];
    newYLarge[1] = oldYLarge[1] + hInter * temp[1];
    while(!(newYLarge[0] <= oldYLarge[0]) || !(newYLarge[1] <= oldYLarge[1])){
        oldYLarge[0] += alpahInter * oldYLarge[0];
        oldYLarge[1] += alpahInter * oldYLarge[1];
        h /= 2;
        INTERVAL newH(0, h);
        hInter = newH;
        f(oldYtight, temp);
        newYLarge[0] = oldYLarge[0] + hInter * temp[0];
        newYLarge[1] = oldYLarge[1] + hInter * temp[1];
    }
    newYLarge[0] = oldYLarge[0];
    newYLarge[1] = oldYLarge[1];
    return h;
}

void step2Eij(INTERVAL* yLarge, REAL h, INTERVAL* yTight, REAL* A, INTERVAL* x, INTERVAL* ySuivLarge, REAL* ASuiv, INTERVAL* xSuiv){
    REAL yMil = INTERVAL.mid(yTight);
}

int main{
    F[0][0] = 0;
    F[0][1] = 1;
    F[1][0] = -1;
    F[1][1] = 0;


    return 0;
}