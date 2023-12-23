#pragma once 
#include <fstream> 
#include <filesystem>

#include "common.h"

namespace fs = std::filesystem; 

class Camera 
{
public: 
    Camera() = default; 
    void Initialize()
    {
        mImageHeight = castInt(mImageWidth / mAspectRatio); 
        std::cout<<"Image Size:"<<mImageWidth<<"x"<<mImageHeight<<std::endl; 

        // camera properties
        mOrigin = math::point3();
        double viewportHeight = 2.0; 
        float focalLength = 1.0; 
        double viewportWidth = viewportHeight * (castFloat(mImageWidth)/mImageHeight);
        std::cout<<"Viewport Size:"<<viewportWidth<<"x"<<viewportHeight<<std::endl; 
        
        // viewport vectors
        mViewportU = math::vec3(viewportWidth, 0, 0); 
        mViewportV = math::vec3(0, -viewportHeight, 0); 
        mViewportW = math::vec3(0, 0, focalLength); 
        
        // pixel spacing
        mPixelDeltaU = mViewportU / mImageWidth;
        mPixelDeltaV = mViewportV / mImageHeight;
    }
    void Render(Hittable const& world)
    {
        fs::path output_path = fs::current_path() / "output.ppm";
        std::ofstream imageFileObject (output_path, std::ios_base::out);
        // ppm header
        // P3
        // w h
        // 255
        imageFileObject<<"P3\n" <<mImageWidth<< ' ' <<mImageHeight<<"\n255\n";
        
        // starting point 
        auto viewportTopLeft = mOrigin - mViewportU/2 - mViewportV/2 - mViewportW; 
        auto pixel00 = viewportTopLeft + 0.5f * (mPixelDeltaU + mPixelDeltaV); 
        for (int h = 0 ; h < mImageHeight; ++h){
            for(int w = 0; w < mImageWidth; ++w){
                math::vec3 currentPoint = pixel00 + mPixelDeltaU * w + mPixelDeltaV * h; 
                math::vec3 direction = currentPoint - mOrigin;
                Ray r(mOrigin, direction); 
                math::color pixelColor = RayColor(r, world); 
                WriteColor(imageFileObject, pixelColor); 
            } 
        }
        imageFileObject.close(); 
    }

    math::color RayColor(Ray const& ray, Hittable const& world)
    {
        HitRecord record; 
        if (world.Hit(ray, Interval(0, Interval::infinity), record)){
            math::color c = 0.5*(math::color(1.0f, 1.0f, 1.0f) + record.normal); 
            return c; 
        }    
        //return background color
        math::vec3 dirNormalized = math::unit_vector(ray.Direction()); 
        double t = 0.5*(dirNormalized.y() + 1.0); 
        return (1.0 - t) * math::color(1.0, 1.0, 1.0) + t * math::color(0.5, 0.7, 1.0); 
    }


    double mAspectRatio; 
    int mImageWidth; 
private: 
    int mImageHeight; 
    math::point3 mOrigin;
    math::vec3 mViewportU ; 
    math::vec3 mViewportV ;
    math::vec3 mViewportW ; 
    math::vec3 mPixelDeltaU;
    math::vec3 mPixelDeltaV;
};

