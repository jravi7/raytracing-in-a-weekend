#include <iostream>
#include <string>
#include <fstream> 
#include <filesystem>


#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "ray.h"


namespace fs = std::filesystem; 
using namespace math; 

bool hitSphere(point3 const& center, double radius, Ray const& r)
{
    //coeefficients of t 
    double a = dot(r.dir, r.dir); 
    double b = 2 * (dot(r.orig, r.dir) - dot(r.dir, center)); 
    double c = -2 * dot(r.orig, center) + dot(r.orig, r.orig) + dot(center, center) - radius * radius; 
    auto discriminant = b * b - 4 * a * c; 
    return discriminant > 0; 
}

color RayColor(Ray const& ray)
{
    point3 const& spherePosition = point3(0,0,-1); 
    double const sphereRadius = 0.5; 
    if (hitSphere(spherePosition, sphereRadius, ray)){
        return color(1, 0, 0); 
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
    float const aspectRatio = 16/9; 
    int const imageHeight = 1080; 
    int const imageWidth = static_cast<int>(imageHeight * aspectRatio); 

    //camera properties
    double viewportHeight = 2.0; 
    double viewportWidth = viewportHeight * aspectRatio;
    float focalLength = 1.0; 

    auto origin = point3();
    auto horizontal = vec3(viewportWidth, 0, 0); 
    auto vertical = vec3(0, viewportHeight, 0); 
    auto lowerLeft = origin - horizontal/2 - vertical/2 - vec3(0,0,focalLength);
    

    fs::path output_path = fs::current_path() / "output.ppm";
    std::ofstream imageFileObject (output_path, std::ios_base::out);

    imageFileObject<<"P3\n" <<imageWidth<< ' ' <<imageHeight<<"\n255\n";

    for (int h = imageHeight - 1; h >=0; --h){
        for(int w = 0; w < imageWidth; ++w){
            auto u = double (w) / (imageWidth - 1);
            auto v = double (h) / (imageHeight - 1);
            vec3 endpoint = lowerLeft + u*horizontal + v * vertical; 
            vec3 direction = endpoint - origin; 
            Ray r(origin, direction); 
            color pixelColor = RayColor(r); 
            WriteColor(imageFileObject, pixelColor); 
        } 
    }
    imageFileObject.close(); 
    std::cerr<<"\nDone.\n";
    return 0; 
}