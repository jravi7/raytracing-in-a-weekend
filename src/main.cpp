#include <iostream>
#include <string>

#include "common.h"
#include "color.h"
#include "sphere.h"
#include "hittable-list.h"
#include "camera.h"

using namespace math; 

color RayColor(Ray const& ray, Hittable const& world)
{
    HitRecord record; 
    if (world.Hit(ray, Interval(0, Interval::infinity), record)){
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

    // image properties
    Camera camera;
    camera.mAspectRatio = 16.0/9.0; 
    camera.mImageWidth = 700; 
    camera.Initialize(); 

    // World - Sekai - Ulagam
    HittableList world; 
    world.Add(std::make_shared<Sphere>(100, point3(0, -100.5, -1)));
    world.Add(std::make_shared<Sphere>(0.5, point3(0, 0, -1)));
    
    camera.Render(world); 

    
    std::cerr<<"\nDone.\n";
    return 0; 
}