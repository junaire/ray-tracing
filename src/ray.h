#pragma once

#include "vec3.h"

class Ray {
 public:
  Ray() = default;
  Ray(Point3 orgin, Vec3 direction)
      : orgin_(std::move(orgin)), direction_(std::move(direction)) {}

  [[nodiscard]] Point3 orgin() const { return orgin_; }
  [[nodiscard]] Vec3 direction() const { return direction_; }

  [[nodiscard]] Point3 at(double t) const { return orgin_ + direction_ * t; }

 private:
  Point3 orgin_;
  Vec3 direction_;
};
