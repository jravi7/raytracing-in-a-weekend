#pragma once 

#include "interval.h"
#include "ray.h"
#include "vec3.h"

#define castInt(x) static_cast<int>(x)
#define castFloat(x) static_cast<float>(x)
#define castDouble(x) static_cast<double>(x)

double const pi = 3.1415926535897932385;

inline double DegreesToRadians(double degree)
{
    return degree * pi / 180.0; 
}

Interval const universe(-Interval::infinity, Interval::infinity);
Interval const empty(Interval::infinity, -Interval::infinity);