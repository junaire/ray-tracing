#pragma once

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
 public:
  Point3 center;
  double radius;

  constexpr Sphere() = default;
  constexpr Sphere(Point3 center_, double radius_)
      : center(std::move(center_)), radius(radius_) {}

  [[nodiscard]] std::optional<HitRecord> hit(const Ray& ray, double tmin,
                                             double tmax) const override;
};
