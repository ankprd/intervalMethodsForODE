#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<BIAS/Bias0.h>

int main(){
    BiasInit();
    REAL i = 3.2;
    REAL f = 4.2;
    BIASINTERVAL i1;
    i1.inf = i;
    i1.sup = f;
    BIASINTERVAL i2 = i1;
    BIASINTERVAL res;
    BiasAddII(&res, &i1, &i2);
    printf("i1 : %lf %lf\n f : %lf %lf\n, res : %lf %lf\n", i1.inf, i1.sup, i2.inf, i2.sup, res.inf, res.sup);

    return 0;
}