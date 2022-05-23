#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "color.h"

color RayColor(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{
    // Image properties
    auto const aspectRatio = 16.0 / 9.0;
    int const imageWidth = 500; 
    int const imageHeight = static_cast<int>(imageWidth / aspectRatio);
    
    // Camera 
    auto viewportHeight = 2.0; 
    auto viewportWidth = aspectRatio * viewportHeight; 
    auto focal_length = 1.0; 
    auto horizontal = vec3(viewportWidth, 0, 0); 
    auto vertical = vec3(0, viewportHeight, 0);
    auto origin = point3(0,0,0); 
    auto lowerLeft = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    std::cout<<"P3\n" <<imageWidth<< ' ' <<imageHeight<<"\n255\n";

    for (int h = imageHeight - 1; h >=0; --h){
        std::cerr << "\rScanlines remaining: " << h << ' ' << std::flush;

        for(int w = 0; w < imageWidth; ++w){
            auto u = double(w) / (imageWidth - 1); 
            auto v = double(h) / (imageHeight - 1); 
            ray r(origin, lowerLeft + u * horizontal + v * vertical - origin);
            color pixelColor (double (w) / (imageWidth - 1), double (h) / (imageHeight - 1), 0.25); 
            color pixel_color = RayColor(r);
            WriteColor(std::cout, pixel_color);
        } 
    }
    std::cerr<<"\nDone.\n";
    return 0; 
}