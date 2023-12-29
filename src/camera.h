#pragma once 
#include <fstream> 
#include <filesystem>

#include "common.h"
#include "material.h"

namespace fs = std::filesystem; 

class Camera 
{
public: 
    Camera() = default; 
    void Initialize()
    {
        ImageHeight = castInt(ImageWidth / AspectRatio); 
        std::cout<<"Image Size:"<<ImageWidth<<"x"<<ImageHeight<<std::endl; 

        // camera properties
        mOrigin = math::point3();
        double viewportHeight = 2.0; 
        float focalLength = 1.0; 
        double viewportWidth = viewportHeight * (castFloat(ImageWidth)/ImageHeight);
        std::cout<<"Viewport Size:"<<viewportWidth<<"x"<<viewportHeight<<std::endl; 
        
        // viewport vectors
        mViewportU = math::vec3(viewportWidth, 0, 0); 
        mViewportV = math::vec3(0, -viewportHeight, 0); 
        mViewportW = math::vec3(0, 0, focalLength); 
        
        // pixel spacing
        mPixelDeltaU = mViewportU / ImageWidth;
        mPixelDeltaV = mViewportV / ImageHeight;
        // starting point 
        auto viewportTopLeft = mOrigin - mViewportU/2 - mViewportV/2 - mViewportW; 
        mPixel00 = viewportTopLeft + 0.5f * (mPixelDeltaU + mPixelDeltaV); 
    }
    void Render(Hittable const& world)
    {
        fs::path output_path = fs::current_path() / "output.ppm";
        std::ofstream imageFileObject (output_path, std::ios_base::out);
        // ppm header
        // P3
        // w h
        // 255
        imageFileObject<<"P3\n" <<ImageWidth<< ' ' <<ImageHeight<<"\n255\n";
        
        for (int h = 0 ; h < ImageHeight; ++h){
            for(int w = 0; w < ImageWidth; ++w){
                math::color pixelColor = math::point3();
                for(int sample = 0; sample < SamplesPerPixels; sample++){
                    Ray r = GetRay(w, h);
                    pixelColor += RayColor(r, world, MaxDepth);     
                }
                WriteColor(imageFileObject, pixelColor, SamplesPerPixels); 
            } 
        }
        imageFileObject.close(); 
    }


    double AspectRatio; 
    int ImageWidth; 
    int ImageHeight; 
    int SamplesPerPixels; 
    int MaxDepth; 
private: 
    Ray GetRay(int ii, int jj) const
    {   
        math::point3 pixelCenter = mPixel00 + ii * mPixelDeltaU + jj * mPixelDeltaV;
        math::point3 pixelSample = pixelCenter + PixelSampleSquare(); 
        math::vec3 direction = pixelSample - mOrigin;
        return Ray(mOrigin, direction); 
    }
    math::point3 PixelSampleSquare() const
    {
        double px = -0.5 + RandomDouble(); 
        double py = -0.5 + RandomDouble(); 
        return px * mPixelDeltaU + py * mPixelDeltaV;
    }
    math::color RayColor(Ray const& ray, Hittable const& world, int depth)
    {   
        if (depth <= 0){
            return math::color(0,0,0); 
        }
        HitRecord record; 
        if (world.Hit(ray, Interval(0.001, Interval::infinity), record)){ //0.001 is to avoid Shadow Acne
            Ray scattered;
            math::color attenuation; 
            if (record.material->Scatter(ray, record, attenuation, scattered)){
                return attenuation * RayColor(scattered, world, depth-1); 
            }
            return math::color(0,0,0); 
        }    
        //return background color
        math::vec3 dirNormalized = math::unit_vector(ray.Direction()); 
        double t = 0.5*(dirNormalized.y() + 1.0); 
        return (1.0 - t) * math::color(1.0, 1.0, 1.0) + t * math::color(0.5, 0.7, 1.0); 
    }

    math::point3 mPixel00; 
    math::point3 mOrigin;
    math::vec3 mViewportU ; 
    math::vec3 mViewportV ;
    math::vec3 mViewportW ; 
    math::vec3 mPixelDeltaU;
    math::vec3 mPixelDeltaV;
};

