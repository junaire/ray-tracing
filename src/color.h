#pragma once

#include <cmath>
#include <iostream>

#include "vec3.h"

// make sure x is in the range of [min, max]
inline double clamp(double x, double min, double max) {
  if (x < min) {
    return min;
  }
  if (x > max) {
    return max;
  }
  return x;
}

void writeColor(std::ostream& os, const Color& pixel, int samplePerPixel) {
  auto r = pixel.x();
  auto g = pixel.y();
  auto b = pixel.z();

  auto scale = 1.0 / samplePerPixel;
  r *= scale * r;
  g *= scale * g;
  b *= scale * b;

  os << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << " "
     << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << " "
     << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << "\n";
}
