#pragma once

#include <memory>
#include <optional>

#include "ray.h"
#include "vec3.h"

class Material;

struct HitRecord {
  HitRecord() = default;
  HitRecord(Point3 p_, Vec3 normal_, double t_)
      : p(std::move(p)), normal(std::move(normal_)), t(t_) {}

  void setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
    frontFace = dot(ray.direction(), outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
  }

  Point3 p;
  Vec3 normal;
  double t;
  bool frontFace;
  Material* matPtr;
};

class Hittable {
 public:
  [[nodiscard]] virtual std::optional<HitRecord> hit(const Ray& ray,
                                                     double tmin,
                                                     double tmax) const = 0;
};
