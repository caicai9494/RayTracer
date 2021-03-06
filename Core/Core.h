////////////////////////////////////////
// Core.h
////////////////////////////////////////

#ifndef CSE168_CORE_H
#define CSE168_CORE_H

////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <ctype.h>
#include <ctime>
#include <memory>

const float PI	= 3.14159265f;
const float RAYOFFSET = 0.0001f;
const int MaxTrianglesPerBox = 100;
const int MaxDepth = 10;
const int SuperSampling = 2;


typedef unsigned int UINT;
inline float Rand1()
{
    return float(rand())/RAND_MAX;
}
inline float RangeRand(float lower, float up)
{
    return float(rand())/RAND_MAX * (up - lower) + lower;
}

inline float Min(float a,float b)			{return a<b ? a : b;}
inline float Min(float a, float b, float c)
{
    return Min(Min(a,b), c);
}
inline int Min(int a,int b)					{return a<b ? a : b;}
inline int Max(int a,int b)					{return a>b ? a : b;}
inline float Max(float a,float b)			{return a>b ? a : b;}
inline float Max(float a, float b, float c)
{
    return Max(Max(a,b), c);
}
inline int Clamp(int x,int a,int b)			{if(x<a) return a; if(x>b) return b; return x;}
inline float Clamp(float x,float a,float b)	{if(x<a) return a; if(x>b) return b; return x;}

////////////////////////////////////////////////////////////////////////////////

#endif
