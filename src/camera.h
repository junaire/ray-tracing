#pragma once

#include "ray.h"
#include "vec3.h"

static constexpr auto aspectRadio = 16.0 / 9.0;
static constexpr auto viewportHeight = 2.0;
static constexpr auto viewportWidth = aspectRadio * viewportHeight;
static constexpr auto focalLength = 1.0;

class Camera {
 public:
  Camera()
      : origin({0, 0, 0}),
        horizontal({viewportWidth, 0, 0}),
        vertical({0, viewportHeight, 0}) {
    lowerLeftCorner =
        origin - (horizontal / 2) - (vertical / 2) - Vec3{0, 0, focalLength};
  }

  [[nodiscard]] Ray getRay(double u, double v) const;

 private:
  Point3 origin;
  Point3 lowerLeftCorner;
  Vec3 horizontal;
  Vec3 vertical;
};
