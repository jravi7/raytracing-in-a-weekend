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

class Dielectric : public Material {
  public:
    Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    bool Scatter(const Ray& rayIn, const HitRecord& rec, math::color& attenuation, Ray& scattered) const override 
    {
        attenuation = math::color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.frontFace ? (1.0/ir) : ir;

        math::vec3 unit_direction = unit_vector(rayIn.Direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        math::vec3 direction;
        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > RandomDouble())
            direction = math::reflect(unit_direction, rec.normal);
        else
            direction = math::refract(unit_direction, rec.normal, refraction_ratio);

        scattered = Ray(rec.point, direction);
        return true;
    }

  private:
    double ir; // Index of Refraction

    static double reflectance(double cosine, double ref_idx) {
        // Use Schlick's approximation for reflectance.
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};