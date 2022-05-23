#include <iostream>
#include "vec3.h"
#include "color.h"

int main()
{
    int const imageWidth = 256; 
    int const imageHeight = 256; 

    std::cout<<"P3\n" <<imageWidth<< ' ' <<imageHeight<<"\n255\n";

    for (int h = imageHeight - 1; h >=0; --h){
        std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;

        for(int w = 0; w < imageWidth; ++w){
            // auto r = double (w) / (imageWidth - 1);
            // auto g = ;
            // auto b = 0.25; 
            color pixelColor (double (w) / (imageWidth - 1), double (h) / (imageHeight - 1), 0.25); 
            WriteColor(std::cout, pixelColor); 
        } 
    }
    std::cerr<<"\nDone.\n";
    return 0; 
}