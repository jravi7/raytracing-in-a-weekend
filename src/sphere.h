# pragma once
#include "hittable.h"


class Sphere: public Hittable
{
public: 
    Sphere(float radius, math::point3 center, std::shared_ptr<Material> material): 
        mRadius(radius), mCenter(center), mMaterial(material)
    {

    }

    bool Hit(Ray const& r, Interval const& rayInterval, HitRecord& record) const override
    {
        //coeefficients of t 
        math::vec3 oc = r.orig - mCenter; 
        double a = r.dir.length_squared(); 
        double half_b = dot(oc, r.dir); 
        double c = dot(oc, oc) - mRadius * mRadius; 
        double discriminant = half_b * half_b - a * c; 
        double sqrtD = sqrt(discriminant); 

        if (discriminant < 0.0) {
            return false; 
        } 
        double root = (-half_b-sqrtD) / a;
        if(!rayInterval.Surrounds(root)){
            root = (-half_b+sqrtD) / a;
            if (!rayInterval.Surrounds(root)){
                return false; 
            }
        }
        record.t = root; 
        record.point = r.At(root); 
        record.SetFaceNormal(r,(record.point - mCenter) / mRadius); 
        record.material = mMaterial;
        return true; 
    }

private: 
    float mRadius;   
    math::point3 mCenter; 
    std::shared_ptr<Material> mMaterial; 
};