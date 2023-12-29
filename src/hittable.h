# pragma once
#include "interval.h"
#include "vec3.h"
#include "ray.h"
#include <memory>

class Material; 

struct HitRecord
{
    bool frontFace; 
    double t; 
    math::point3 point; 
    math::vec3 normal; 
    std::shared_ptr<Material> material; 

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
    virtual bool Hit(Ray const& r, Interval const& rayInterval, HitRecord& record) const = 0; 
};