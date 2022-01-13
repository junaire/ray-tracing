#pragma once

#include "vec3.h"

class Ray {
 public:
  constexpr Ray() = default;
  constexpr Ray(Point3 origin, Vec3 direction)
      : origin_(std::move(origin)), direction_(std::move(direction)) {}

  [[nodiscard]] constexpr Point3 origin() const { return origin_; }
  [[nodiscard]] constexpr Vec3 direction() const { return direction_; }

  [[nodiscard]] constexpr Point3 at(double t) const {
    return origin_ + (direction_ * t);
  }

 private:
  Point3 origin_;
  Vec3 direction_;
};
