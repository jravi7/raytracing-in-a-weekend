#include <iostream>
#include <string>
#include <fstream> 
#include <filesystem>


#include "common.h"
#include "color.h"
#include "sphere.h"
#include "hittable-list.h"


#define castInt(x) static_cast<int>(x)
#define castFloat(x) static_cast<float>(x)
#define castDouble(x) static_cast<double>(x)

namespace fs = std::filesystem; 
using namespace math; 

color RayColor(Ray const& ray, Hittable const& world)
{
    HitRecord record; 
    if (world.Hit(ray, 0, infinity, record)){
        color c = 0.5*(color(1.0f, 1.0f, 1.0f) + record.normal); 
        return c; 
    }    
    //return background color
    vec3 dirNormalized = math::unit_vector(ray.Direction()); 
    double t = 0.5*(dirNormalized.y() + 1.0); 
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); 
}

int main(int argc, char** argv)
{
    std::string outputImagePath = "output.ppm";
    if (argc > 1){
        outputImagePath = std::string(argv[0]); 
    }

    //image properties
    float const aspectRatio = 16.0/9.0;
    int const imageWidth = 700; 
    int const imageHeight = castInt(imageWidth / aspectRatio); 
    std::cout<<"Image Size:"<<imageWidth<<"x"<<imageHeight<<std::endl; 

    //camera properties
    point3 cameraOrigin = point3();
    double viewportHeight = 2.0; 
    double viewportWidth = viewportHeight * (castFloat(imageWidth)/imageHeight);
    std::cout<<"Viewport Size:"<<viewportWidth<<"x"<<viewportHeight<<std::endl; 
    float focalLength = 1.0; 

    // viewport vectors
    vec3 viewportU = vec3(viewportWidth, 0, 0); 
    vec3 viewportV = vec3(0, -viewportHeight, 0); 
    vec3 viewportW = vec3(0, 0, focalLength); 
    // pixel spacing
    vec3 du = viewportU / imageWidth;
    vec3 dv = viewportV / imageHeight;
    // starting point 
    auto viewportTopLeft = cameraOrigin - viewportU/2 - viewportV/2 - viewportW; 
    auto pixel00 = viewportTopLeft + 0.5f * (du + dv); 

    // World - Sekai - Ulagam
    HittableList world; 
    world.Add(std::make_shared<Sphere>(100, point3(0, -100.5, -1)));
    world.Add(std::make_shared<Sphere>(0.5, point3(0, 0, -1)));
    
    

    fs::path output_path = fs::current_path() / "output.ppm";
    std::ofstream imageFileObject (output_path, std::ios_base::out);
    // ppm header
    // P3
    // w h
    // 255
    imageFileObject<<"P3\n" <<imageWidth<< ' ' <<imageHeight<<"\n255\n";

    for (int h = 0 ; h < imageHeight; ++h){
        for(int w = 0; w < imageWidth; ++w){
            vec3 currentPoint = pixel00 + du * w + dv * h; 
            vec3 direction = currentPoint - cameraOrigin;
            Ray r(cameraOrigin, direction); 
            color pixelColor = RayColor(r, world); 
            WriteColor(imageFileObject, pixelColor); 
        } 
    }
    imageFileObject.close(); 
    std::cerr<<"\nDone.\n";
    return 0; 
}