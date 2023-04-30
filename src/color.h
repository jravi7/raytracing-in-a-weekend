#pragma once

#include "vec3.h"

#include <iostream>

void WriteColor(std::ostream &out, math::color const& pixelColor) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255 * pixelColor.x()) << ' '
        << static_cast<int>(255 * pixelColor.y()) << ' '
        << static_cast<int>(255 * pixelColor.z()) << '\n';
}
