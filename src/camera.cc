#include "camera.h"

Ray Camera::getRay(double s, double t) const {
  Vec3 rd = lensRadius * randomInUnitDisk();
  Vec3 offset = u * rd.x() + v * rd.y();

  return {origin + offset, lowerLeftCorner + (s * horizontal) + (t * vertical) -
                               origin - offset};
}
