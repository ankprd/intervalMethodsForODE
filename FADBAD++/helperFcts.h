#ifndef _FADBAD_Helper
#define _FADBAD_Helper

#include <math.h>
#include<BIAS/Bias0.h>
#include<BIAS/BiasF.h>
#include <stdexcept>

template<typename T> 
T& helperAddBIASINTERVAL(BIASINTERVAL& x, const T& y) { 
	throw std::invalid_argument( "unimplemented type of add");
	//return x+=y; 
}
template<>
BIASINTERVAL& helperAddBIASINTERVAL(BIASINTERVAL& x, const BIASINTERVAL& y){
	BIASINTERVAL res;
	BiasAddII(&res, &x, &y);
	x = res;
	return x;
}
BIASINTERVAL& helperAddBIASINTERVAL(BIASINTERVAL& x, const REAL& y){
	BIASINTERVAL res;
	BiasAddIR(&res, &x, &y);
	x = res;
	return x;
}

template<typename T> 
T& helperSubBIASINTERVAL(BIASINTERVAL& x, const T& y) { 
	throw std::invalid_argument( "unimplemented type of sub");
	//return x+=y; 
}
template<>
BIASINTERVAL& helperSubBIASINTERVAL(BIASINTERVAL& x, const BIASINTERVAL& y){
	BIASINTERVAL res;
	BiasSubII(&res, &x, &y);
	x = res;
	return x;
}
//template<>
BIASINTERVAL& helperSubBIASINTERVAL(BIASINTERVAL& x, const REAL& y){
	BIASINTERVAL res;
	BiasSubIR(&res, &x, &y);
	x = res;
	return x;
}

template<typename T> 
T& helperMulBIASINTERVAL(BIASINTERVAL& x, const T& y) { 
	throw std::invalid_argument( "unimplemented type of mul");
	//return x+=y; 
}
template<>
BIASINTERVAL& helperMulBIASINTERVAL(BIASINTERVAL& x, const BIASINTERVAL& y){
	BIASINTERVAL res;
	BiasMulII(&res, &x, &y);
	x = res;
	return x;
}
BIASINTERVAL& helperMulBIASINTERVAL(BIASINTERVAL& x, const REAL& y){
	BIASINTERVAL res;
	BiasMulIR(&res, &x, &y);
	x = res;
	return x;
}

template<typename T> 
T& helperDivBIASINTERVAL(BIASINTERVAL& x, const T& y) { 
	throw std::invalid_argument( "unimplemented type of div");
	//return x+=y; 
}
template<>
BIASINTERVAL& helperDivBIASINTERVAL(BIASINTERVAL& x, const BIASINTERVAL& y){
	BIASINTERVAL res;
	BiasDivII(&res, &x, &y);
	x = res;
	return x;
}
BIASINTERVAL& helperDivBIASINTERVAL(BIASINTERVAL& x, const REAL& y){
	BIASINTERVAL res;
	BiasDivIR(&res, &x, &y);
	x = res;
	return x;
}

template <typename X, typename Y>
BIASINTERVAL helperPow(const X& x, const Y& y) {
	throw std::invalid_argument( "unimplemented type of pow");
	//return x+=y; 
}
template<>
BIASINTERVAL helperPow(const BIASINTERVAL& x, const int& y){
	BIASINTERVAL res;
	BiasPowerN (&res, &x, y);
	return res;
    //return ::my_pow(x,y); 
}

#endif