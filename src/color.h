#pragma once

#include "vec3.h"

#include <iostream>

double LinearToGamma(double linearComponent)
{
    return sqrt(linearComponent); 
}

void WriteColor(std::ostream &out, math::color const& pixelColor, int samplesPerPixel) {
    double r = pixelColor.x(); 
    double g = pixelColor.y(); 
    double b = pixelColor.z(); 

    double scaleFactor = 1.0 / samplesPerPixel; 
    r *= scaleFactor;
    g *= scaleFactor;
    b *= scaleFactor;

    r = LinearToGamma(r);    
    g = LinearToGamma(g);     
    b = LinearToGamma(b); 
    
    // Write the translated [0,255] value of each color component.
    static const Interval intensity(0.000, 0.999);

    out << static_cast<int>(256 * intensity.clamp(r)) << ' '
        << static_cast<int>(256 * intensity.clamp(g)) << ' '
        << static_cast<int>(256 * intensity.clamp(b)) << '\n';
}
