#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include<BIAS/Bias0.h>
#include<vector>

/*Methode du cours sur x' = -x, x(0) = 1*/

/*typedef struct BoundingBox {
    BIASINTERVAL interTime;
    BIASINTERVAL interVals;

    BoundingBox () {}
    BoundingBox(BIASINTERVAL utT, BIASINTERVAL utV) : interTime(utT), interVals(utV) {}
} BoundingBox;*/

REAL factorialOfInt(int n){
    REAL res = 1;
    REAL temp = 1;
    for(int i = 1; i <=n; i++){
        res *= temp;
        temp += 1;
    }
    return res;
}

REAL power(REAL h, int n){
    REAL res = 1;
    for(int i = 0; i <= n; i++)
        res *= h;
    return res;
}

BIASINTERVAL f(BIASINTERVAL* x){
    BIASINTERVAL res;
    BiasNeg(&res, x);
    return res;
}

BIASINTERVAL taylorF(BIASINTERVAL x, int iTaylor){
    if(iTaylor %2 == 1){
        return f(&x);
    }
    return x;
}

REAL step1(BIASINTERVAL* presB, BIASINTERVAL Xi, REAL maxH, REAL t){
    REAL h = 2 * maxH;
    BIASINTERVAL Btemp = Xi;
    BIASINTERVAL* pBtemp = &Btemp;
    BIASINTERVAL res = Xi;
    BIASINTERVAL* pres = &res;
    do {
        pBtemp = pres;
        h /= 2;
        printf("Pour h = %lf et t = %lf : \n", h, t);
        BIASINTERVAL fB = f(pBtemp);
        BIASINTERVAL timeInter = {t, t + h};
        BIASINTERVAL prod;
        BiasMulII(&prod, &timeInter, &fB);
        //printf("Prod = [%lf, %lf ]\n", prod.inf, prod.sup);
        BiasAddII(pres, &Xi, &prod);
        printf("Et res = [%lf, %lf] et included ? %d\n\n", pres->inf, pres->sup, BiasInI(pres, pBtemp));
    } while (!BiasInI(pres, pBtemp));
    *presB = *pBtemp;
    return h;
}

BIASINTERVAL calcInterTaylor(BIASINTERVAL inter, REAL h, int iTaylor){
    REAL coeff = power(h, iTaylor) / factorialOfInt(iTaylor);
    BIASINTERVAL temp = taylorF(inter, iTaylor);
    BIASINTERVAL res;
    BiasMulRI(&res, &coeff, &temp);
    return res;
}

BIASINTERVAL step2(BIASINTERVAL Xi, BIASINTERVAL B, REAL h, int nTaylor){
    BIASINTERVAL res = Xi;
    for(int idTaylor = 1; idTaylor < nTaylor; idTaylor++){
        BIASINTERVAL temp;
        BIASINTERVAL interTaylor = calcInterTaylor(Xi, h, idTaylor);
        printf("Pour idTaylor = %d, res avt = [%lf, %lf ] et interTaylor = [%lf, %lf ]\n", idTaylor, res.inf, res.sup, interTaylor.inf, interTaylor.sup);
        BiasAddII(&temp, &interTaylor, &res);
        res = temp;
    }
    BIASINTERVAL temp;
    BIASINTERVAL interTaylor = calcInterTaylor(B, h, nTaylor);
    printf("Pour idTaylor = %d, res avt = [%lf, %lf ] et interTaylor = [%lf, %lf ]\n", nTaylor, res.inf, res.sup, interTaylor.inf, interTaylor.sup);
    BiasAddII(&temp, &res, &interTaylor);
    res = temp;
    printf("Donc final res : [%lf, %lf]\n", res.inf, res.sup);
    return res;
}



int main(){
    BiasInit();

    //std::vector<BoundingBox> boundingBoxes;
    int nbTimeStepsMax = 1;
    BIASINTERVAL interCalc;
    interCalc.inf = 0;
    interCalc.sup = 1;
    REAL maxH = 1;
    int nTaylor = 4;
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
        REAL h = step1(&B, Xi, maxH, t);
        //BIASINTERVAL timei = {t, t + h};
        //boundingBoxes.push_back(BoundingBox(timei, B));

        printf("at time %lf : B = [ %lf, %lf ] and step %lf and Xi : [%lf, %lf]\n", t, B.inf, B.sup, h, Xi.inf, Xi.sup);

        //Step2
        BIASINTERVAL Xisuiv = step2(Xi, B, h, nTaylor);

        printf("at time %lf : Xi+1 = [ %lf, %lf ]\n", t + h, Xisuiv.inf, Xisuiv.sup);

        Xi = Xisuiv;
        t += h;
    }

    return 0;
}