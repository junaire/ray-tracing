#pragma once

#include <memory>

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
 public:
  Point3 center;
  double radius;
  Material* matPtr;

  constexpr Sphere() = default;
  Sphere(Point3 center_, double radius_, Material* matPtr_)
      : center(std::move(center_)), radius(radius_), matPtr(matPtr_) {}

  [[nodiscard]] std::optional<HitRecord> hit(const Ray& ray, double tmin,
                                             double tmax) const override;
};
