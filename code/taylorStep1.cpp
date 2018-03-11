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

INTERVAL calcU(REAL h, INTERVAL y0, INTERVAL Xi, int nTaylor){
    INTERVAL res = Xi;
    INTERVAL hI(0, h);
    INTERVAL hIPuiss(0, h);
    TODE ode;                // Construct ODE:
	ode.x[0]=Xi;              // Set point of expansion:
	for(int i=0;i<nTaylor;i++)
	{
		ode.xp.eval(i); // Evaluate i'th Taylor coefficient
		ode.x[i+1]=ode.xp[i]/INTERVAL(i+1);// Use dx/dt=ode(x).
	}
    for(int i = 1; i < nTaylor; i++){
        INTERVAL c = ode.x[i];
        res = res + c * hIPuiss;
        hIPuiss = hIPuiss * hI;
        //cout << "Pour idTaylor = " << i << " interTaylor = " <<  c << " et newRes = " << res << endl;
    }
    TODE odeB;                // Construct ODE:
    odeB.x[0]=y0;              // Set point of expansion:
	for(int i=0;i<=nTaylor;i++)
	{
		odeB.xp.eval(i); // Evaluate i'th Taylor coefficient
		odeB.x[i+1]=odeB.xp[i]/INTERVAL(i+1);// Use dx/dt=ode(x).
	}
    res = res + ode.x[nTaylor] * hIPuiss;
    return res;
}

REAL step1Taylor(INTERVAL& B, INTERVAL Xi, REAL maxH, REAL t, int nTaylor){
    REAL h = maxH;
    F<INTERVAL> f, x;
    x = Xi;
    f = func(x);
    INTERVAL y0 = f.x();
    cout << "y0 = " << y0 << endl;
    while(1){
        INTERVAL y1 = calcU(h, y0, Xi, nTaylor);
        cout << "prem calc : y1 = " << y1 << endl;
        if(y1 <= y0){
            cout << "y1 inclus dans y0 -> out" << endl;
            B = calcU(h, y1, Xi, nTaylor);
            return h;
        }
        else{
            cout << "y1 pas inclus dans y0" << endl;
            y0 = y1;
            y1 = calcU(h, y1, Xi, nTaylor);
            cout << "new y0 " << y0 << " new y1 " << y1 << endl;
            if(y1 <= y0){
                cout << "y1 inclus dans y0 -> out" << endl;
                B = calcU(h, y1, Xi, nTaylor);
                return h;
            }
            else
                h /= 2;
            cout << "y1 pas inclus dans y0, newH " << h << endl;
        }
    }
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
        //cout << "Pour idTaylor = " << i << " interTaylor = " <<  c << " et newRes = " << res << endl;
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
    REAL maxH = 0.5;
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
        REAL h = step1Taylor(B, Xi, maxH, t, nTaylor);
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