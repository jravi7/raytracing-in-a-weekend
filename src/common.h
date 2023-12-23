#pragma once 

#include "interval.h"
#include "ray.h"
#include "vec3.h"

double const pi = 3.1415926535897932385;

inline double DegreesToRadians(double degree)
{
    return degree * pi / 180.0; 
}

Interval const universe(-Interval::infinity, Interval::infinity);
Interval const empty(Interval::infinity, -Interval::infinity);