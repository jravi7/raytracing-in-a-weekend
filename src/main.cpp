#include <iostream>
#include <string>

#include "common.h"
#include "color.h"
#include "sphere.h"
#include "hittable-list.h"
#include "camera.h"

using namespace math; 

int main(int argc, char** argv)
{
    std::string outputImagePath = "output.ppm";
    if (argc > 1){
        outputImagePath = std::string(argv[0]); 
    }

    // image properties
    Camera camera;
    camera.AspectRatio = 16.0/9.0; 
    camera.ImageWidth = 700; 
    camera.SamplesPerPixels = 100; 
    camera.MaxDepth = 50; 
    camera.Initialize(); 

    // World - Sekai - Ulagam
    HittableList world; 
    world.Add(std::make_shared<Sphere>(100, point3(0, -100.5, -1)));
    world.Add(std::make_shared<Sphere>(0.5, point3(0, 0, -1)));
    
    camera.Render(world); 

    
    std::cerr<<"\nDone.\n";
    return 0; 
}