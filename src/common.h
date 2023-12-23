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

inline double RandomDouble()
{
    return rand() / (RAND_MAX + 1.0); 
}

inline double RandomDouble(double min, double max)
{
    return min + (max-min) * RandomDouble(); 
}

Interval const universe(-Interval::infinity, Interval::infinity);
Interval const empty(Interval::infinity, -Interval::infinity);