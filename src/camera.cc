#include "camera.h"

Ray Camera::getRay(double s, double t) const {
  return {origin, lowerLeftCorner + (s * horizontal) + (t * vertical) - origin};
}
