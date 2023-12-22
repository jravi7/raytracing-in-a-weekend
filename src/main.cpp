#include <iostream>
#include <string>
#include <fstream> 
#include <filesystem>


#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "ray.h"

#define castInt(x) static_cast<int>(x)
#define castFloat(x) static_cast<float>(x)
#define castDouble(x) static_cast<double>(x)

namespace fs = std::filesystem; 
using namespace math; 

double hitSphere(point3 const& center, double radius, Ray const& r)
{
    //coeefficients of t 
    vec3 oc = r.orig - center; 
    double a = r.dir.length_squared(); 
    double half_b = dot(oc, r.dir); 
    double c = -2 * oc.length_squared() + dot(r.orig, r.orig) + dot(center, center) - radius * radius; 
    auto discriminant = half_b * half_b -  a * c; 
    if (discriminant > 0.0){
        return (-half_b-sqrt(discriminant)) / a; 
    } else {
        return -1.0; 
    }
}

color RayColor(Ray const& ray)
{
    // point3 const& spherePosition = point3(0,0,-1); 
    // double const sphereRadius = 0.5; 
    // double t = hitSphere(spherePosition, sphereRadius, ray);
    // if (t > 0.0){
    //     vec3 n = math::unit_vector(ray.At(t) - spherePosition);
    //     color c = 0.5*(color(n.x()+1, n.y()+1, n.z()+1)); 
    //     return c; 
    // }    
    //return background color
    vec3 dirNormalized = math::unit_vector(ray.Direction()); 
    auto t = 0.5*(dirNormalized.y() + 1.0); 
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
    int const imageWidth = 400; 
    int const imageHeight = castInt(imageWidth / aspectRatio); 
    std::cout<<"Image Size:"<<imageWidth<<"x"<<imageHeight<<std::endl; 

    //camera properties
    double viewportHeight = 2.0; 
    double viewportWidth = viewportHeight * (castFloat(imageWidth)/imageHeight);
    std::cout<<"Viewport Size:"<<viewportWidth<<"x"<<viewportHeight<<std::endl; 
    float focalLength = 1.0; 

    auto cameraOrigin = point3();
    // viewport vectors
    auto viewportU = vec3(viewportWidth, 0, 0); 
    auto viewportV = vec3(0, viewportHeight, 0); 
    auto viewportW = vec3(0, 0, focalLength); 
    // pixel spacing
    auto du = viewportU / castFloat(imageWidth);
    auto dv = viewportV / castFloat(imageHeight);
    
    // starting 
    auto viewportTopLeft = cameraOrigin - viewportU/2 + viewportV/2 - viewportW; 
    auto pixel00 = viewportTopLeft + 0.5f * (du + dv); 
    

    fs::path output_path = fs::current_path() / "output.ppm";
    std::ofstream imageFileObject (output_path, std::ios_base::out);
    // ppm header
    // P3
    // w h
    // 255
    imageFileObject<<"P3\n" <<imageWidth<< ' ' <<imageHeight<<"\n255\n";

    for (int h = 0 ; h < imageHeight; ++h){
        for(int w = 0; w < imageWidth; ++w){
            auto u = double (w) / (imageWidth - 1);
            auto v = double (h) / (imageHeight - 1);
            vec3 currentPoint = pixel00 + du * w + dv * v; 
            vec3 direction = currentPoint - cameraOrigin;
            Ray r(cameraOrigin, direction); 
            color pixelColor = RayColor(r); 
            WriteColor(imageFileObject, pixelColor); 
        } 
    }
    imageFileObject.close(); 
    std::cerr<<"\nDone.\n";
    return 0; 
}