#pragma once

#include "vec3.h"

class Ray 
{
public: 
    Ray(){}
    Ray(math::point3 const& origin, math::vec3 const& direction ):
        orig(origin), dir(direction) {}

    math::point3 Origin() const {return orig;}
    math::point3 Direction() const {return dir;}

    math::point3 At(double t) const{
            return orig + t * dir; 
        }

public: 
    math::point3 orig;
    math::vec3 dir;
};