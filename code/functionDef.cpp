#include "fadiff.h"
#include "tadiff.h"
#include "functionDef.h"

using namespace std;
using namespace fadbad;

F<INTERVAL> func(const F<INTERVAL>& x)
{
	return -x;
}

T<INTERVAL> funcT(const T<INTERVAL>& x)
{
	return -x;
}