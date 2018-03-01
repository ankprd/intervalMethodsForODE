// Copyright (C) 1996-2007 Ole Stauning & Claus Bendtsen (fadbad@uning.dk)
// All rights reserved.

// This code is provided "as is", without any warranty of any kind,
// either expressed or implied, including but not limited to, any implied
// warranty of merchantibility or fitness for any purpose. In no event
// will any party who distributed the code be liable for damages or for
// any claim(s) by any other party, including but not limited to, any
// lost profits, lost monies, lost data or data rendered inaccurate,
// losses sustained by third parties, or any other special, incidental or
// consequential damages arising out of the use or inability to use the
// program, even if the possibility of such damages has been advised
// against. The entire risk as to the quality, the performance, and the
// fitness of the program for any particular purpose lies with the party
// using the code.

// This code, and any derivative of this code, may not be used in a
// commercial package without the prior explicit written permission of
// the authors. Verbatim copies of this code may be made and distributed
// in any medium, provided that this copyright notice is not removed or
// altered in any way. No fees may be charged for distribution of the
// codes, other than a fee to cover the cost of the media and a
// reasonable handling fee.

// ***************************************************************
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE TERMS OF THE
//                         COPYRIGHT NOTICE
// ***************************************************************

#ifndef _FADBAD_H
#define _FADBAD_H

//#include <math.h>
//#include<BIAS/Bias0.h>
//#include<BIAS/BiasF.h>
//#include <stdexcept>
#include<helperFcts.h>

namespace fadbad
{
	// NOTE:
	// The following template allows the user to change the operations that
	// are used in FADBAD++ for computing the derivatives. This is useful 
	// for example for specializing with non-standard types such as interval 
	// arithmetic types.
	template <typename T> struct Op // YOU MIGHT NEED TO SPECIALIZE THIS TEMPLATE:
	{
		typedef T Base;
		static Base myInteger(const int i) { return Base(i); }
		static Base myZero() { return myInteger(0); }
		static Base myOne() { return myInteger(1);}
		static Base myTwo() { return myInteger(2); }
		static Base myPI() { return 3.14159265358979323846; }
		static T myPos(const T& x) { return +x; }
		static T myNeg(const T& x) { return -x; }
		template <typename U> static T& myCadd(T& x, const U& y) { return x+=y; }
		template <typename U> static T& myCsub(T& x, const U& y) { return x-=y; }
		template <typename U> static T& myCmul(T& x, const U& y) { return x*=y; }
		template <typename U> static T& myCdiv(T& x, const U& y) { return x/=y; }
		static T myInv(const T& x) { return myOne()/x; }
		static T mySqr(const T& x) { return x*x; }
		template <typename X, typename Y>
		static T myPow(const X& x, const Y& y) { return ::pow(x,y); }
		static T mySqrt(const T& x) { return ::sqrt(x); }
		static T myLog(const T& x) { return ::log(x); }
		static T myExp(const T& x) { return ::exp(x); }
		static T mySin(const T& x) { return ::sin(x); }
		static T myCos(const T& x) { return ::cos(x); }
		static T myTan(const T& x) { return ::tan(x); }
		static T myAsin(const T& x) { return ::asin(x); }
		static T myAcos(const T& x) { return ::acos(x); }
		static T myAtan(const T& x) { return ::atan(x); }
		static bool myEq(const T& x, const T& y) { return x==y; }
		static bool myNe(const T& x, const T& y) { return x!=y; }
		static bool myLt(const T& x, const T& y) { return x<y; }
		static bool myLe(const T& x, const T& y) { return x<=y; }
		static bool myGt(const T& x, const T& y) { return x>y; }
		static bool myGe(const T& x, const T& y) { return x>=y; }
	};

	/*template <> struct Op<BIASINTERVAL>
	{
		typedef BIASINTERVAL Base;
		static Base myInteger(const int i) {
			BIASINTERVAL res = {(double) i, double (i)}; 
			return res; 
		}
		static Base myZero() { return myInteger(0); }
		static Base myOne() { return myInteger(1);}
		static Base myTwo() { return myInteger(2); }
		static Base myPI() { 
			BIASINTERVAL res = {3.14159265358979323846, 3.14159265358979323846}; 
			return res;
			}
		static BIASINTERVAL myPos(const BIASINTERVAL& x) { return x; }
		static BIASINTERVAL myNeg(const BIASINTERVAL& x) { 
			BIASINTERVAL res;
			BiasNeg(&res, &x);
			return res; 
		}
		template <typename U> static BIASINTERVAL& myCadd(BIASINTERVAL& x, const U& y) { 
			return helperAddBIASINTERVAL(x, y);
			//return x+=y; 
		}
		
		template <typename U> static BIASINTERVAL& myCSub(BIASINTERVAL& x, const U& y) { 
			return helperSubBIASINTERVAL(x, y);
			//return x+=y; 
		}
	
		template <typename U> static BIASINTERVAL& myCmul(BIASINTERVAL& x, const U& y) { 
			return helperMulBIASINTERVAL(x, y);
			//return x+=y; 
		}
		
		template <typename U> static BIASINTERVAL& myCdiv(BIASINTERVAL& x, const U& y) { 
			return helperDivBIASINTERVAL(x, y);
			//return x+=y; 
		}

		static BIASINTERVAL myInv(const BIASINTERVAL& x) { 
			BIASINTERVAL temp = myOne();
			return myCdiv(temp, x);	
		}

		static BIASINTERVAL mySqr(const BIASINTERVAL& x) { 
			BIASINTERVAL res;
			BiasMulII(&res, &x, &x);
			return res;
		}

		template <typename X, typename Y>
		static BIASINTERVAL myPow(const X& x, const Y& y) {
			return herlperPow(x, y);
		}
		static BIASINTERVAL mySqrt(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasSqrt(&res, &x);
			return res; 
		}
		static BIASINTERVAL myLog(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasLog(&res, &x);
			return res; 
		}
		static BIASINTERVAL myExp(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasExp(&res, &x);
			return res; 
		}
		static BIASINTERVAL mySin(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasSin(&res, &x);
			return res; 
		}
		static BIASINTERVAL myCos(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasCos(&res, &x);
			return res; 
		}
		static BIASINTERVAL myTan(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasTan(&res, &x);
			return res; 
		}
		static BIASINTERVAL myAsin(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasArcSin(&res, &x);
			return res; 
		}
		static BIASINTERVAL myAcos(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasArcCos(&res, &x);
			return res; 
		}
		static BIASINTERVAL myAtan(const BIASINTERVAL& x) {
			BIASINTERVAL res;
			BiasArcTan(&res, &x);
			return res; 
		}
		static bool myEq(const BIASINTERVAL& x, const BIASINTERVAL& y) { return BiasIsEqual(&x, &y); }
		static bool myNe(const BIASINTERVAL& x, const BIASINTERVAL& y) { return 1 - BiasIsEqual(&x, &y); }
		static bool myLt(const BIASINTERVAL& x, const BIASINTERVAL& y) { throw std::invalid_argument( "no less than"); }
		static bool myLe(const BIASINTERVAL& x, const BIASINTERVAL& y) { throw std::invalid_argument( "no less or eq than"); }
		static bool myGt(const BIASINTERVAL& x, const BIASINTERVAL& y) { throw std::invalid_argument( "no greater than"); }
		static bool myGe(const BIASINTERVAL& x, const BIASINTERVAL& y) { throw std::invalid_argument( "no greater or eq than"); }
	};*/

	template <> struct Op<INTERVAL>
	{
		typedef MyType Base;
		static Base myInteger(const int i) { return Base(i); }
		static Base myZero() { return myInteger(0); }
		static Base myOne() { return myInteger(1);}
		static Base myTwo() { return myInteger(2); }
		static Base myPI() { return MyType(3.14159265358979323846); }
		static MyType myPos(const MyType& x) { return +x; }
		static MyType myNeg(const MyType& x) { return -x; }
		template <typename U> static MyType& myCadd(MyType& x, const U& y) { return x+=y; }
		template <typename U> static MyType& myCsub(MyType& x, const U& y) { return x-=y; }
		template <typename U> static MyType& myCmul(MyType& x, const U& y) { return x*=y; }
		template <typename U> static MyType& myCdiv(MyType& x, const U& y) { return x/=y; }
		static MyType myInv(const MyType& x) { return myOne()/x; }
		static MyType mySqr(const MyType& x) { return x*x; }
		template <typename X, typename Y>
		static MyType myPow(const X& x, const Y& y) { return ::my_pow(x,y); }
		static MyType mySqrt(const MyType& x) { return ::my_sqrt(x); }
		static MyType myLog(const MyType& x) { return ::my_log(x); }
		static MyType myExp(const MyType& x) { return ::my_exp(x); }
		static MyType mySin(const MyType& x) { return ::my_sin(x); }
		static MyType myCos(const MyType& x) { return ::my_cos(x); }
		static MyType myTan(const MyType& x) { return ::my_tan(x); }
		static MyType myAsin(const MyType& x) { return ::my_asin(x); }
		static MyType myAcos(const MyType& x) { return ::my_acos(x); }
		static MyType myAtan(const MyType& x) { return ::my_atan(x); }
		static bool myEq(const MyType& x, const MyType& y) { return x==y; }
		static bool myNe(const MyType& x, const MyType& y) { return x!=y; }
		static bool myLt(const MyType& x, const MyType& y) { return x<y; }
		static bool myLe(const MyType& x, const MyType& y) { return x<=y; }
		static bool myGt(const MyType& x, const MyType& y) { return x>y; }
		static bool myGe(const MyType& x, const MyType& y) { return x>=y; }
	};
} //namespace fadbad

// Name for backward AD type:
#define BTypeName B

// Name for forward AD type:
#define FTypeName F

// Name for taylor AD type:
#define TTypeName T

// Should always be inline:
#define INLINE0 inline

// Methods with only one line:
#define INLINE1 inline

// Methods with more than one line:
#define INLINE2 inline

#ifdef __SUNPRO_CC
// FOR SOME REASON SOME INLINES CAUSES 
// UNRESOLVED SMBOLS ON SUN.
#undef INLINE0
#undef INLINE1
#undef INLINE2
#define INLINE0
#define INLINE1
#define INLINE2
#endif

// Define this if you want assertions, etc..
#ifdef _DEBUG

#include <sstream>
#include <iostream>

inline void ReportError(const char* errmsg)
{
	std::cout<<errmsg<<std::endl;
}

#define USER_ASSERT(check,msg)\
	if (!(check))\
	{\
		std::ostringstream ost;\
		ost<<"User assertion failed: \""<<msg<<"\", at line "<<__LINE__<<", file "<<__FILE__<<std::endl;\
		ReportError(ost.str().c_str());\
	}
#define INTERNAL_ASSERT(check,msg)\
	if (!(check))\
	{\
		std::ostringstream ost;\
		ost<<"Internal error: \""<<msg<<"\", at line "<<__LINE__<<", file "<<__FILE__<<std::endl;\
		ReportError(ost.str().c_str());\
	}
#define ASSERT(check)\
	if (!(check))\
	{\
		std::ostringstream ost;\
		ost<<"Internal error at line "<<__LINE__<<", file "<<__FILE__<<std::endl;\
		ReportError(ost.str().c_str());\
	}
#ifdef _TRACE
#define DEBUG(code) code;
#else
#define DEBUG(code)
#endif

#else

#define USER_ASSERT(check,msg)
#define INTERNAL_ASSERT(check,msg)
#define ASSERT(check)
#define DEBUG(code)

#endif

#endif



