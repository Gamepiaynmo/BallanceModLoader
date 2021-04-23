/*************************************************************************/
/*	File : XUtil.h														 */
/*	Author :  Aymeric Bard												 */	
/*																		 */	
/*	Virtools SDK 															 */	 
/*	Copyright (c) Virtools 2000, All Rights Reserved.						 */	
/*************************************************************************/

#ifndef _XUTIL_H_
#define _XUTIL_H_

#include "math.h"
#include "stdlib.h"


#ifdef macintosh
	#include "VxMacHeader.h"
	#pragma cpp_extensions on
#endif

#ifdef _DEBUG
	#if defined(WIN32) || defined(_XBOX)
		#ifdef _WIN32_WCE
			
			#define _DEBUG_BREAKPOINT() 
		#else
			#if _XBOX_VER<200 
				#define _DEBUG_BREAKPOINT() __asm { int 3 } 
			#else
				#define _DEBUG_BREAKPOINT() DebugBreak();
			#endif
		#endif
	#else
		
		#define _DEBUG_BREAKPOINT() 
	#endif
#else
	
	#define _DEBUG_BREAKPOINT() 
#endif 

#define _QUOTE(x) # x

#define QUOTE(x) _QUOTE(x)

#define __FILE__LINE__ __FILE__ "(" QUOTE(__LINE__) ") : "

#define NOTE( x )  message( x )

#define FILE_LINE  message( __FILE__LINE__ )

#define TODO( x )  message( __FILE__LINE__"\n"           \
        " ------------------------------------------------\n" \
        "|  TODO :   " #x "\n" \
        " -------------------------------------------------\n" )

#define TOFIX( x )  message(  __FILE__LINE__"\n"           \
        " ------------------------------------------------\n" \
        "|  TOFIX :  " #x "\n" \
        " -------------------------------------------------\n" )

#define todo( x )  message( __FILE__LINE__" TODO :   " #x "\n" ) 

#define tofix( x )  message( __FILE__LINE__" TOFIX:   " #x "\n" ) 

#ifndef XBYTE
typedef unsigned char XBYTE;		
#endif

#ifndef XBOOL
typedef int XBOOL;					
#endif

#ifndef XWORD
typedef unsigned short XWORD;		
#endif

#ifndef XDWORD
typedef unsigned int XDWORD;		
#endif

// TODO : specify which OS does not support assert here
#ifndef _WIN32_WCE
	#ifdef PSX2
		#ifdef DEBUG
			
			#define XASSERT(a)	if(!(a)) { asm(" breakc 0x0"); asm(" nop");}
		#else
			#define XASSERT(a)	
		#endif
	#else
		#include <cassert>
		#define XASSERT(a)	assert(a)
	#endif
#else
	#define XASSERT(a) 
#endif

#ifndef VX_EXPORT
#define VX_EXPORT
#endif

#ifdef WIN32
	// Summary: Sort function prototype for XArray,XBinaryTree sort operations
	// 
	typedef int (__cdecl  *VxSortFunc)(const void *elem1, const void *elem2 );
#else
	typedef int (*VxSortFunc)(const void *elem1, const void *elem2 );
#endif

//*************** X86 ASM DEFINES *************************************************

#if defined(WIN32) || defined(_XBOX)
	#ifndef _WIN32_WCE
		
		#if (_XBOX_VER<200)
			#define ASM_SUPPORTED
		#endif
	#endif
#endif


#ifdef ASM_SUPPORTED
#pragma warning (disable:4035)
	// 
	inline float XCos(float f) {
		__asm {
		fld dword ptr f
		fcos
		}
	}
	// 
 	inline  float XSin(float f) {
		__asm {
			fld dword ptr f
			fsin
		}
	}
#pragma warning (default:4035)
#else 
	inline float XCos(float f) {
		return (float)cos(f);
	}
	inline float XSin(float f) {
		return (float)sin(f);
	}
#endif

	


/*************************************************
Summary: Enables the initialisation of a reference from two values.

Arguments:
	iCond:  TRUE to return iT1 , FALSE to return iT2;
*************************************************/
template <class T>
const T& ChooseRef(XBOOL iCond, const T& iT1, const T& iT2)
{
	if (iCond)
		return iT1;
	else 
		return iT2;
}

/*************************************************
Summary: Forces a value in an interval.

Arguments:
	t:  value to threshold
	min: minimum valid value
	max: maximum valid value
See Also: XMin,XMax
*************************************************/
template <class T>
void XThreshold(T& t,const T& min,const T& max) 
{
	if (t < min) t = min;
	else if (t > max) t = max;
}


/*************************************************
Summary: Returns the minimum of two values.

Remarks:
	Returns minimum between a and b.



See Also: XMax
*************************************************/
template <class T>
const T& XMin(const T& a,const T& b) 
{
	if(a < b) return a;
	else return b;
}

/*************************************************
Summary: Returns the maximum of two values.

Remarks:
	Returns maximum between a and b.



See Also: XMax
*************************************************/
template <class T>
const T& XMax(const T& a,const T& b) 
{
	if(a > b) return a;
	else return b;
}

/*************************************************
Summary: Finds the minimum and maximum of 2 values.

Remarks:
	Returns minimum and maximum between a,b.



See Also: XMin,XMax
*************************************************/
template <class T>
void XMinMax(const T& a,const T& b, T& min, T& max) 
{
	if (a<b) {
		min = a;
		max = b;
	} else {
		min = b;
		max = a;
	}
}

/*************************************************
Summary: Returns the minimum of two values.

Remarks:
	Returns minimum between a,b and c.



See Also: XMax
*************************************************/
template <class T>
const T& XMin(const T& a,const T& b,const T& c) 
{
	return (a<b)?((c<a)?c:a):((c<b)?c:b);
}

/*************************************************
Summary: Returns the maximum of two values.

Remarks:
	Returns maximum between a,b and c.



See Also: XMin
*************************************************/
template <class T>
const T& XMax(const T& a,const T& b,const T& c) 
{
	return (a>b)?((c>a)?c:a):((c>b)?c:b);
}

/*************************************************
Summary: Finds the minimum and maximum of 3 values.

Remarks:
	Returns minimum and maximum between a,b and c.



See Also: XMin,XMax
*************************************************/
template <class T>
void XMinMax(const T& a,const T& b,const T& c, T& min, T& max) 
{
	if (a<b) {
		if (c<a) {
			min = c;
			max = b;
		} else {
			min = a;
			if (b<c)	max = c;
			else		max = b;
		}
	} else {
		if (c<b) {
			min = c;
			max = a;
		} else {
			min = b;
			if (a<c)	max = c;
			else		max = a;
		}
	}
}

template <class T>
void XMinMax(const T& a,const T& b,const T& c, T& min, T& med, T& max) 
{
	if (a<b) {
		if (c<a) {
			min = c;
			med = a;
			max = b;
		} else {
			min = a;
			if (b<c) {
				med = b;
				max = c;
			} else {
				med = c;
				max = b;
			}
		}
	} else {
		if (c<b) {
			min = c;
			med = b;
			max = a;
		} else {
			min = b;
			if (a<c) {
				max = c;
				med = a;
			} else {
				max = a;
				med = c;
			}
		}
	}
}

/*************************************************
Summary: Swaps two elements.

Remarks:
	Swaps a and b.	


*************************************************/
template <class T>
void XSwap(T& a,T& b) 
{
	T c = a;
	a = b;
	b = c;
}
/*************************************************
Summary: Returns the absolute value of a.

Remarks:

*************************************************/
template <class T>
T XAbs(T a)
{
	return (a>0)?a:-a;
}

// float specialization
#ifdef macintosh
	template <> inline float XAbs<float>(float a) {return (float)__fabs(a);}
#else
	template <> inline float XAbs<float>(float a) {return (float)::fabs(a);}
#endif

/*************************************************
Summary: Returns the absolute value of a float.

Remarks:

*************************************************/
inline float XFabs(float a)
{
#ifdef macintosh
	return (float)__fabs((double)a);
#else
	return (float)::fabs((double)a);
#endif
	//return *(float*)&( (*(int*)(&a)) & 0xF800);
}

//------ Memory Management

#define VxNew(a) (new unsigned char[a])

#define VxDelete(a) (delete[] (unsigned char*) a)


template <class T> T* VxAllocate	(int n);

template <class T> void VxFree		(T* t);


inline int LowestBitMask(int v)
{
	return ((v & -v));
}

/*************************************************
Summary: return true if num is a power of 2

Remarks:

*************************************************/
inline XBOOL						Is2Power(int x)
{
	return x != 0 && x == LowestBitMask(x);
}

/*************************************************
Summary: return the nearest superior power of 2 of v

Remarks:

*************************************************/
inline int						Near2Power(int v)
{
	int i = LowestBitMask(v);
	while(i < v)
		i <<= 1;
	return i;
}

#if defined(macintosh)

	/*************************************************
	Summary: perform a right bit rotation (emulates _rotl & _rotr of Windows' Stdlib)
	Remarks:
	Macintosh only
	
	*************************************************/
	inline int _rotr(int v, int shift)
	{
		const int invShift 	= 32 - shift;
		const int mask 		= (1 << invShift) - 1;
		return ((v >> shift) & mask) | (v << invShift);
	}

	/*************************************************
	Summary: perform a left bit rotation (emulates _rotl & _rotr of Windows' Stdlib)
	Remarks:
	Macintosh only
	
	*************************************************/
	inline int _rotl(int v, int shift)
	{
		const int invShift 	= 32 - shift;
		const int mask 		= (1 << invShift) - 1;
		return ((v >> invShift) & mask) | (v << shift);
	}

#endif

/*******************************************************************************
Summary: Global Unique Identifier Struture.

Remarks: Comparison operators are defined so XGUIDS can be compared with 
==,!= ,<,> operators.
*******************************************************************************/
class XGUID
{
public:
	
	explicit XGUID(XDWORD gd1=0,XDWORD gd2=0)
		: d1(gd1),d2(gd2)
	{
	}
	
	friend XBOOL operator==(const XGUID& v1,const XGUID& v2) 
	{
		return ((v1.d1==v2.d1)&&(v1.d2==v2.d2));
	}
	
	friend XBOOL operator!=(const XGUID& v1,const XGUID& v2) 
	{
		return ((v1.d1!=v2.d1)||(v1.d2!=v2.d2));
	}
	
	friend XBOOL operator<(const XGUID& v1,const XGUID& v2) 
	{
		if(v1.d1<v2.d1)
			return true;
		if(v1.d1==v2.d1)
			return (v1.d2<v2.d2);
		return false;
	}
	
	friend XBOOL operator<=(const XGUID& v1,const XGUID& v2) 
	{ 	
		return (v1.d1<=v2.d1);
	}
	
	friend XBOOL operator>(const XGUID& v1,const XGUID& v2) 
	{
		if(v1.d1>v2.d1)
			return true;
		if(v1.d1==v2.d1)
			return (v1.d2>v2.d2);
		return false;
	}
	
	friend XBOOL operator>=(const XGUID& v1,const XGUID& v2) 
	{ 
		return (v1.d1>=v2.d1);
	}

	
	XBOOL inline IsValid()
	{
		return d1&&d2;
	}

	XDWORD d1;
	XDWORD d2;
};




#endif
