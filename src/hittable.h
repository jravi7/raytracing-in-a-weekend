# pragma once
#include "vec3.h"
#include "ray.h"

struct HitRecord
{
    bool frontFace; 
    double t; 
    math::point3 point; 
    math::vec3 normal; 

    //! @brief Set unit face normal
    void SetFaceNormal(Ray const& r, math::vec3 const& outwardNormal)
    {
        frontFace = math::dot(r.dir, outwardNormal) < 0; 
        normal = frontFace ? outwardNormal: -outwardNormal; 
    }
};

class Hittable
{
public: 
    virtual ~Hittable() = default; 
    virtual bool Hit(Ray const& r, double tmin, double tmax, HitRecord& record) const = 0; 
};