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

math::vec3 RandomVec3()
{
    return math::vec3(RandomDouble(), RandomDouble(), RandomDouble()); 
}

math::vec3 RandomVec3(double min, double max)
{
    return math::vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max)); 
}

inline math::vec3 RandomVec3InUnitSphere()
{
    while(true){
        math::vec3 p = RandomVec3(-1, 1); 
        if(p.length_squared() < 1){
            return p; 
        }
    }
}

inline math::vec3 RandomUnitVector() 
{
    // return unit_vector(RandomVec3InUnitSphere()); //Book's approach
    // My approach. Intuition - get any random vector and make it a vector on the
    // unit sphere.
    return unit_vector(RandomVec3(-1, 1)); 
}

inline math::vec3 RandomOnHemisphere(math::vec3 const& normal)
{
    math::vec3 vectorOnUnitSphere = RandomUnitVector(); 
    double dotProduct = math::dot(vectorOnUnitSphere, normal); 
    if (dotProduct < 0.0){
        vectorOnUnitSphere = -vectorOnUnitSphere; 
    }
    return vectorOnUnitSphere; 
}


Interval const universe(-Interval::infinity, Interval::infinity);
Interval const empty(Interval::infinity, -Interval::infinity);