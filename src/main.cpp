#include <iostream>
#include <fstream> 
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <filesystem>

namespace fs = std::filesystem; 

int main(int argc, char** argv)
{
    //image properties
    float const aspectRatio = 16/9; 
    int const imageHeight = 1080; 
    int const imageWidth = imageHeight * aspectRatio; 

    //camera properties
    int viewportHeight = 2.0f; 
    int viewportWidth = viewportHeight * aspectRatio; 
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
            auto r = double (w) / (imageWidth - 1);
            auto g = double (h) / (imageHeight - 1);
            auto b = 0.25;  
            color pixelColor (r, g, b); 
            WriteColor(imageFileObject, pixelColor); 
        } 
    }
    imageFileObject.close(); 
    std::cerr<<"\nDone.\n";
    return 0; 
}