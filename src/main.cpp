#include <iostream>
#include <fstream> 
#include "vec3.h"
#include "color.h"
#include <filesystem>

namespace fs = std::filesystem; 

int main()
{
    int const imageWidth = 1024; 
    int const imageHeight = 768; 

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