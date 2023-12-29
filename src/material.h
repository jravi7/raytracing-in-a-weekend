#pragma once

#include "common.h"


class HitRecord; 

class Material
{   
public: 
    ~Material() = default; 
    virtual bool Scatter(Ray const& rayIn, HitRecord const& record, math::color& attenuation, Ray& scattered) const = 0; 

};

class Lambertian: public Material
{
public: 
    Lambertian(math::color albedo): mAlbedo(albedo){}
    
    bool Scatter(Ray const& rayIn, HitRecord const& record, math::color& attenuation, Ray& scattered) const override
    {
        math::vec3 scatterDirection = record.normal + RandomUnitVector(); 
        if(scatterDirection.near_zero()){
            scatterDirection = record.normal;
        }
        scattered = Ray(record.point, scatterDirection); 
        attenuation = mAlbedo; 
        return true; 
    }   

private: 
    math::color mAlbedo; 
};

class Metal: public Material
{
public: 
    Metal(math::color albedo, double fuzz): mAlbedo(albedo), mFuzz(fuzz < 1.0 ? fuzz : 1.0){}
    
    bool Scatter(Ray const& rayIn, HitRecord const& record, math::color& attenuation, Ray& scattered) const override
    {
        math::vec3 reflected = math::reflect(math::unit_vector(rayIn.Direction()), record.normal); 
        scattered = Ray(record.point, reflected + mFuzz * RandomUnitVector()); 
        attenuation = mAlbedo; 
        return (math::dot(scattered.Direction(), record.normal) > 0.0); 
    }   

private: 
    math::color mAlbedo; 
    double mFuzz; 
};