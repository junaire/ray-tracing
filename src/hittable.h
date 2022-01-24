#pragma once

#include <memory>
#include <optional>

#include "ray.h"
#include "vec3.h"

class Material;

class HitRecord {
 public:
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
  [[nodiscard]] virtual std::optional<HitRecord> hit(Ray& ray) const = 0;
  virtual ~Hittable() = default;
};

class Sphere : public Hittable {
 public:
  constexpr Sphere() = default;
  Sphere(Point3 center_, double radius_, std::unique_ptr<Material> matPtr_)
      : center(std::move(center_)),
        radius(radius_),
        matPtr(std::move(matPtr_)) {}

  [[nodiscard]] std::optional<HitRecord> hit(Ray& ray) const override;

 private:
  Point3 center;
  double radius;
  std::unique_ptr<Material> matPtr;
};

class HittableList : public Hittable {
 public:
  HittableList() = default;
  explicit HittableList(std::unique_ptr<Hittable> obj) { add(std::move(obj)); }

  void add(std::unique_ptr<Hittable> obj) { objects.push_back(std::move(obj)); }

  void clear() { objects.clear(); }

  [[nodiscard]] std::optional<HitRecord> hit(Ray& ray) const override;

 private:
  std::vector<std::unique_ptr<Hittable>> objects;
};
