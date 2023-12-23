#pragma once 

#include <limits>
#include "ray.h"
#include "vec3.h"

double const infinity = std::numeric_limits<double>::infinity(); 
double const pi = 3.1415926535897932385;

inline double DegreesToRadians(double degree)
{
    return degree * pi / 180.0; 
}