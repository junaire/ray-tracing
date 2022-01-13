#pragma once

#include <iostream>

#include "vec3.h"

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
  r *= scale;
  g *= scale;
  b *= scale;

  os << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << " "
     << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << " "
     << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << "\n";
}
