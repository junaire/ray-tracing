#pragma once

#include "ray.h"
#include "vec3.h"

class Camera {
 public:
  Camera(Point3 from, Point3 at, Vec3 vup, double vfov, double aspectRadio,
         double aperture, double focusDist) {
    auto theta = degreesToRadians(vfov);
    auto h = std::tan(theta / 2);
    auto viewportHeight = 2.0 * h;
    auto viewportWidth = aspectRadio * viewportHeight;

    w = unitVector(from - at);
    u = unitVector(cross(vup, w));
    v = cross(w, u);

    origin = from;
    horizontal = focusDist * viewportWidth * u;
    vertical = focusDist * viewportHeight * v;
    lowerLeftCorner =
        origin - (horizontal / 2) - (vertical / 2) - (focusDist * w);

    lensRadius = aperture / 2;
  }

  [[nodiscard]] Ray getRay(double u, double v) const;

 private:
  Point3 origin;
  Point3 lowerLeftCorner;
  Vec3 horizontal;
  Vec3 vertical;
  Vec3 w;
  Vec3 u;
  Vec3 v;
  double lensRadius;
};
