#pragma once

#include <iostream>

#include "vec3.h"

void writeColor(std::ostream& os, const Color& pixel) {
  os << static_cast<int>(255.999 * pixel.x()) << " "
     << static_cast<int>(255.999 * pixel.y()) << " "
     << static_cast<int>(255.999 * pixel.z()) << "\n";
}

