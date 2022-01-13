#include "camera.h"

Ray Camera::getRay(double u, double v) const {
  return {origin, lowerLeftCorner + (u * horizontal) + (v * vertical) - origin};
}
