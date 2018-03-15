#include "fadiff.h"
#include "tadiff.h"
#include<vector>
#include<cstdio>
using namespace std;
using namespace fadbad;

/*Eijgenraam's method for the system y1'=y2, y2'=y1*/

/*Notations : 
yiTight = enclosure des valeurs de y a tj -> [yi] du papier
yiLarge = enclosure des valeurs de y entre tj et tj+1 -> [yi~] du papier*/

/*MATRIX F;

INTERVAL_VECTOR f(INTERVAL_VECTOR x){
    return F * x;
}

REAL step1(REAL h, REAL alpha, INTERVAL_VECTOR yOld, INTERVAL_VECTOR& yNew){
    INTERVAL_VECTOR B = yOld;

}*/


vector<T<INTERVAL> > func(const vector<T<INTERVAL> >& x)
{
	vector<T<INTERVAL> > res;
    T<INTERVAL> x0 = x[1];
    T<INTERVAL> x1 = x[0] * 6;
    res.push_back(x0);
    res.push_back(x1);
    return res;
}

class TODE
{
public:
	vector<T<INTERVAL> > x;            // Independent variables
	vector<T<INTERVAL> > xp;           // Dependent variables
	TODE() : x(2), xp(2) {xp=func(x);}      // record DAG at construction
};




int main(){
    TODE ode;                // Construct ODE:
    INTERVAL x0(1, 1);

    INTERVAL x1(-2, -2);
        cout << x0 << " " << x1 << endl; 
    //ode.x[0] = xT;
	ode.x[0] = x0;
    ode.x[1] = x1;  
    cout << ode.x[0][0] << " " << ode.x[1][0] << endl;           // Set point of expansion:
	for(int i=0;i<10;i++)
	{
		ode.xp[0].eval(i); // Evaluate i'th Taylor coefficient
        ode.xp[1].eval(i); // Evaluate i'th Taylor coefficient
		ode.x[0][i+1]=ode.xp[0][i]/double(i+1);// Use dx/dt=ode(x).
        ode.x[1][i+1]=ode.xp[1][i]/double(i+1);// Use dx/dt=ode(x).
	}

	// ode.x[0]...ode.x[10] now contains the Taylor-coefficients
	// of the solution of the ODE.

	// Print out the Taylor coefficients for the solution
	// of the ODE:
	for(int i=0;i<=10;i++)
	{
		cout << "x[" << i << "]=";
        cout << ode.x[0][i] << " " << ode.x[1][i];
        cout << endl;   
	}
    return 0;
}