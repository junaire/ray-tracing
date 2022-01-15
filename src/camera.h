#pragma once

#include "ray.h"
#include "vec3.h"

class Camera {
 public:
  Camera(Point3 from, Point3 at, Vec3 vup, double vfov, double aspectRadio) {
    auto theta = degreesToRadians(vfov);
    auto h = std::tan(theta / 2);
    auto viewportHeight = 2.0 * h;
    auto viewportWidth = aspectRadio * viewportHeight;

    auto w = unitVector(from - at);
    auto u = unitVector(cross(vup, w));
    auto v = cross(w, u);

    origin = from;
    horizontal = viewportWidth * u;
    vertical = viewportHeight * v;
    lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - w;
  }

  [[nodiscard]] Ray getRay(double u, double v) const;

 private:
  Point3 origin;
  Point3 lowerLeftCorner;
  Vec3 horizontal;
  Vec3 vertical;
};
