#pragma once

#include <iostream>

#include "vec3.h"

void writeColor(std::ostream& os, const Color& pixel) {
  os << static_cast<int>(255.99 * pixel.x()) << " "
     << static_cast<int>(255.99 * pixel.y()) << " "
     << static_cast<int>(255.99 * pixel.z()) << "\n";
}

