#pragma once

#include "vec3.h"

class Ray 
{
public: 
    Ray(){}
    Ray(point3 const& origin, vec3 const& direction ): 
        orig(origin), dir(direction) {}

        point3 Origin() const {return orig;}
        point3 Direction() const {return dir;}

        point3 At(double t) const{
            return orig + t * dir; 
        }

public: 
    point3 orig;
    vec3 dir; 
};