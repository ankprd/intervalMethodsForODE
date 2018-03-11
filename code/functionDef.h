#ifndef FCTDEF
#define FCTDEF
#include "fadiff.h"
#include "tadiff.h"

class TODE
{
public:
	T<INTERVAL> x;            // Independent variables
	T<INTERVAL> xp;           // Dependent variables
	TODE(){xp=-x;}      // record DAG at construction
};

F<INTERVAL> func(const F<INTERVAL>& x);
T<INTERVAL> funcT(const T<INTERVAL>& x);

#endif