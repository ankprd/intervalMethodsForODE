#include "fadiff.h"
#include "tadiff.h"
#include<Interval.h>
#include<cstdio>
#include <iostream>
using namespace std;
using namespace fadbad;
#include<vector>

/*Methode du cours sur x' = -x, x(0) = 1*/

typedef struct BoundingBox {
    INTERVAL interTime;
    INTERVAL interVals;

    BoundingBox () {}
    BoundingBox(INTERVAL utT, INTERVAL utV) : interTime(utT), interVals(utV) {}
} BoundingBox;

class TODE
{
public:
	T<INTERVAL> x;            // Independent variables
	T<INTERVAL> xp;           // Dependent variables
	TODE(){xp=-x;}      // record DAG at construction
};

/*REAL factorialOfInt(int n){
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
}*/

F<INTERVAL> func(const F<INTERVAL>& x)
{
	return -x;
}

T<INTERVAL> funcT(const T<INTERVAL>& x)
{
	return -x;
}

/*BIASINTERVAL taylorF(BIASINTERVAL x, int iTaylor){
    if(iTaylor %2 == 1){
        return f(&x);
    }
    return x;
}*/

REAL step1(INTERVAL& B, INTERVAL Xi, REAL maxH, REAL t){
    REAL h = 2 * maxH;
    INTERVAL curB = Xi;
    INTERVAL oldB;
    do {
        h /= 2;
        INTERVAL timeInter(0, h);
        printf("Pour h = %lf et t = %lf : \n", h, t);
        oldB = curB;
        F<INTERVAL> f, x;
        x = oldB;
        f = func(x);
        INTERVAL fB = f.x();
        curB = Xi + timeInter * fB;
        cout << "Pour oldB = " << oldB << " on a fB = " << fB << "et curB = " << curB << endl;
    }while(!(curB <= oldB));//tant que curB n'est pas inclus dans oldB
    B = oldB;
    return 2 * h;
}


INTERVAL step2(INTERVAL Xi, INTERVAL B, REAL h, int nTaylor){
    INTERVAL res = Xi;
    TODE ode;                // Construct ODE:
	ode.x[0]=Xi;              // Set point of expansion:
	for(int i=0;i<nTaylor;i++)
	{
		ode.xp.eval(i); // Evaluate i'th Taylor coefficient
		ode.x[i+1]=ode.xp[i]/INTERVAL(i+1);// Use dx/dt=ode(x).
	}
    for(int i = 1; i < nTaylor; i++){
        INTERVAL c = ode.x[i];
        res = res + c;
        cout << "Pour idTaylor = " << i << " interTaylor = " <<  c << " et newRes = " << res << endl;
    }
    
    TODE odeB;                // Construct ODE:
	odeB.x[0]=B;              // Set point of expansion:
	for(int i=0;i<nTaylor + 1;i++)
	{
		odeB.xp.eval(i); // Evaluate i'th Taylor coefficient
		odeB.x[i+1]=odeB.xp[i]/INTERVAL(i+1);// Use dx/dt=ode(x).
	}
    res = res + odeB.x[nTaylor];
    cout << "final res  " << res << endl;
    return res;
    /*BIASINTERVAL res = Xi;
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
    return res;*/


}




int main(){
    vector<BoundingBox> boundingBoxes;
    int nbTimeStepsMax = 1 ;
    INTERVAL interCalc(0, 1);
    REAL maxH = 1;
    int nTaylor = 4;
    REAL t = 0;
    int iStep = 0;
    INTERVAL Xi(1, 1);
    //on fait sans alpha, juste on diminue h

    while(t < Sup(interCalc)){
        if(iStep >= nbTimeStepsMax){
            printf("Reached nbStepsMax at pos : %lf\n", t);
            break;
        }
        iStep++;

        //Step 1
        INTERVAL B;
        REAL h = step1(B, Xi, maxH, t);
        INTERVAL timei(t, t + h);
        boundingBoxes.push_back(BoundingBox(timei, B));

        cout << "at time " << t << "B = " << B << "and Xi = " << Xi << "and h " << h << endl;

        //Step2
        INTERVAL Xisuiv = step2(Xi, B, h, nTaylor);

        cout << "at time " << t + h << "Xi +1 = " << Xisuiv << endl;;

        Xi = Xisuiv;
        t += h;
    }

    return 0;
}