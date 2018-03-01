#include "fadiff.h"
#include<Interval.h>
#include <iostream>
using namespace std;
using namespace fadbad;

/*Same as in Examplefadbad but with intervals*/

F<INTERVAL> func(const F<INTERVAL>& x, const F<INTERVAL>& y)
{
	F<INTERVAL> z=sqrt(x);
	return y*z+sin(z);
}

int main()
{
	F<INTERVAL> x,y,f;     // Declare variables x,y,f
    INTERVAL xt(1);
    x = xt;                // Initialize variable x
	x.diff(0,2);         // Differentiate with respect to x (index 0 of 2)
	INTERVAL yt(2);
    y = yt;                 // Initialize variable y
	y.diff(1,2);         // Differentiate with respect to y (index 1 of 2)
	f=func(x,y);         // Evaluate function and derivatives
	INTERVAL fval=f.x();   // Value of function
	INTERVAL dfdx=f.d(0);  // Value of df/dx (index 0 of 2)
	INTERVAL dfdy=f.d(1);  // Value of df/dy (index 1 of 2)

	cout << "f(x,y)= " << fval << endl;
	cout << "df/dx(x,y)= "<< dfdx << endl;
	cout << "df/dy(x,y)= " << dfdy << endl;

	return 0;
}
