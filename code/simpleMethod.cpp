#include "fadiff.h"
#include "tadiff.h"
#include<vector>
#include<cstdio>
using namespace std;
using namespace fadbad;

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

F<INTERVAL> func(const F<INTERVAL>& x)
{
	return -x;
}

T<INTERVAL> funcT(const T<INTERVAL>& x)
{
	return -x;
}

REAL step1SimpleMethod(INTERVAL& B, INTERVAL Xi, REAL maxH, REAL t, REAL alpha){
    REAL h = 2 * maxH;
    INTERVAL curB = Xi;
    INTERVAL oldB;
    INTERVAL alphaI(-alpha, alpha);
    int notFirstStep = 0;
    do {
        h /= 2;
        INTERVAL timeInter(0, h);
        printf("Pour h = %lf et t = %lf : \n", h, t);
        oldB = curB;
        if(notFirstStep){
            notFirstStep = 1;
            oldB = oldB + alphaI * oldB;
        }
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


INTERVAL step2SimpleMethod(INTERVAL Xi, INTERVAL B, REAL h, int nTaylor){
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
}




int main(){
    vector<BoundingBox> boundingBoxes;
    int nbTimeStepsMax = 1 ;
    INTERVAL interCalc(0, 1);
    REAL maxH = 1;
    REAL alpha = 0.05;
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
        REAL h = step1SimpleMethod(B, Xi, maxH, t, alpha);
        INTERVAL timei(t, t + h);
        boundingBoxes.push_back(BoundingBox(timei, B));

        cout << "at time " << t << "B = " << B << "and Xi = " << Xi << "and h " << h << endl;

        //Step2
        INTERVAL Xisuiv = step2SimpleMethod(Xi, B, h, nTaylor);

        cout << "at time " << t + h << "Xi +1 = " << Xisuiv << endl;;

        Xi = Xisuiv;
        t += h;
    }
    string na = "simpleMethod.txt";
    //printBoundingBoxesToFile(na, boundingBoxes);
    return 0;
}