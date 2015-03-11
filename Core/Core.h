////////////////////////////////////////
// Core.h
////////////////////////////////////////

#ifndef CSE168_CORE_H
#define CSE168_CORE_H

////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ctime>

#define PI	3.14159265f


typedef unsigned int UINT;
inline float RangeRand(float lower, float up)
{
    return float(rand())/RAND_MAX * (up - lower) + lower;
}

inline int Min(int a,int b)					{return a<b ? a : b;}
inline float Min(float a,float b)			{return a<b ? a : b;}
inline int Max(int a,int b)					{return a>b ? a : b;}
inline float Max(float a,float b)			{return a>b ? a : b;}
inline int Clamp(int x,int a,int b)			{if(x<a) return a; if(x>b) return b; return x;}
inline float Clamp(float x,float a,float b)	{if(x<a) return a; if(x>b) return b; return x;}

////////////////////////////////////////////////////////////////////////////////

#endif
