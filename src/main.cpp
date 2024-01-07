#include <iostream>
#include <string>

#include "common.h"
#include "color.h"
#include "sphere.h"
#include "hittable-list.h"
#include "material.h"
#include "camera.h"

using namespace math; 

int main(int argc, char** argv)
{
    std::string outputImagePath = "output.ppm";
    if (argc > 1){
        outputImagePath = std::string(argv[0]); 
    }

    auto materialGround = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto materialLeft   = std::make_shared<Dielectric>(1.5);
    auto materialRight  = std::make_shared<Metal>(color(0.8, 0.6, 0.2), 0.0);
    // World - Sekai - Ulagam
    HittableList world; 
    world.Add(std::make_shared<Sphere>(100, point3( 0, -100.5, -1.0), materialGround));
    world.Add(std::make_shared<Sphere>(0.5, point3( 0, 0, -1.0), materialCenter));
    world.Add(std::make_shared<Sphere>(0.5, point3(-1.0, 0, -1.0), materialLeft));
    world.Add(std::make_shared<Sphere>(-0.4, point3(-1.0, 0, -1.0), materialLeft));
    world.Add(std::make_shared<Sphere>(0.5, point3( 1.0, 0, -1.0), materialRight));
    
    
    
    // image properties
    Camera camera;
    camera.AspectRatio = 16.0/9.0; 
    camera.ImageWidth = 700; 
    camera.SamplesPerPixels = 100; 
    camera.MaxDepth = 10; 
    camera.Initialize(); 
    camera.Render(world); 

    
    std::cerr<<"\nDone.\n";
    return 0; 
}