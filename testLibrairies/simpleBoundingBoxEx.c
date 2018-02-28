#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<BIAS/Bias0.h>
#include<vector>

/*Methode du cours sur x' = -x, x(0) = 1*/

typedef struct BoundingBox {
    BIASINTERAL interTime;
    BIASINTERVAL interVals;

    BoundingBox () {}
    BoundingBox(BIASINTERVAL utT, BIASINTERVAL utV) : interTime(utT), interVals(utV) {}
}

BIASINTERVAL f(BIASINTERVAL* x){
    BIASINTERVAL res;
    BiasNeg(&res, x);
    return res;
}

REAL step1(BIASINTERVAL* presB, BIASINTERVAL* pXi, BIASINTERVAL ptimeInter, REAL maxH, REAL t){
    REAL h = 2 * maxH;
    BIASINTERVAL* pBtemp = pXi;
    do {
        h /= 2;
        BIASINTERVAL fB = f(pBtemp);
        BIASINTERVAL timeInter = {t, t + h};
        BIASINTERVAL prod;
        BiasMulII(&prod, &timeInter, &fB);
        BIASINTERVAL res;
        BiasAddII(&res, pXi, &prod);
    } while (!BiasInI(&res, pBtemp))
    *presB = *pBtemp;
    return h;
}

BIASINTERVAL step2(BIASINTERVAL Xi, BIASINTERVAL B, REAL h, int nTaylor){
    BIASINTERVAL res = Xi;
    for(int idTaylor = 1; idTaylor <= nTaylor; idTaylor++){

    }
}



int main(){
    BiasInit();

    std::vector<BoundingBox> boundingBoxes;
    int nbTimeStepsMax = 20;
    BIASINTERVAL interCalc;
    interCalc.inf = 0;
    interCalc.sup = 1;
    REAL maxH = 1;
    int nTaylor = 3;
    REAL t = interCalc.inf;
    int iStep = 0;
    BIASINTERVAL Xi;
    Xi.inf = 1;
    Xi.sup = 1;
    //on fait sans alpha, juste on diminue h

    while(t < interCalc.sup){
        if(iStep >= nbTimeStepsMax){
            printf("Reached nbStepsMax at pos : %lf\n", t);
            break;
        }
        iStep++;

        //Step 1
        BIASINTERVAL B;
        REAL h = step1(&B, &Xi, maxH, t);
        BIASINTERVAL time = {t, t + h};
        boundingBoxes.push_back(BoundingBox(time, B));

        //Step2
        BIASINTERVAL Xisuiv = step2(Xi, B, h);

        Xi = Xisuiv;

    }


    return 0;
}