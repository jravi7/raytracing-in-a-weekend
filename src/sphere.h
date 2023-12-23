# pragma once
#include "hittable.h"


class Sphere: public Hittable
{
public: 
    Sphere(float radius, math::point3 center): 
        mRadius(radius), mCenter(center)
    {

    }

    bool Hit(Ray const& r, double tmin, double tmax, HitRecord& record) const override
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
        if(root <= tmin || root >= tmax){
            root = (-half_b+sqrtD) / a;
            if (root <= tmin || root >= tmax){
                return false; 
            }
        }
        record.t = root; 
        record.point = r.At(root); 
        record.SetFaceNormal(r,(record.point - mCenter) / mRadius); 
        return true; 
    }

private: 
    float mRadius;   
    math::point3 mCenter; 
};