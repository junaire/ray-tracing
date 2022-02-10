#pragma once

#include <fmt/format.h>

#include <algorithm>
#include <cmath>
#include <iostream>

#include "vec3.h"

void writeColor(std::ostream& os, const Color& pixel, int samplePerPixel) {
  auto r = pixel.x();
  auto g = pixel.y();
  auto b = pixel.z();

  auto scale = 1.0 / samplePerPixel;
  r *= std::sqrt(scale * r);
  g *= std::sqrt(scale * g);
  b *= std::sqrt(scale * b);

  os << fmt::format("{} {} {}\n",
                    static_cast<int>(256 * std::clamp(r, 0.0, 0.999)),
                    static_cast<int>(256 * std::clamp(r, 0.0, 0.999)),
                    static_cast<int>(256 * std::clamp(r, 0.0, 0.999)));
}
