#include "hittable.h"

#include <cmath>

#include "material.h"

std::optional<HitRecord> Sphere::hit(Ray& ray) const {
  Vec3 oc = ray.origin() - center;
  auto a = ray.direction().lengthSquared();
  auto halfb = dot(oc, ray.direction());
  auto c = oc.lengthSquared() - radius * radius;
  auto discriminant = halfb * halfb - a * c;

  // The equation has no real roots.
  if (discriminant < 0) {
    return std::nullopt;
  }

  auto sqrtd = std::sqrt(discriminant);

  auto root = (-halfb - sqrtd) / a;
  if (root < Ray::getRayMin() || root > ray.getRayMax()) {
    root = (-halfb + sqrtd) / a;
    if (root < Ray::getRayMin() || root > ray.getRayMax()) {
      return std::nullopt;
    }
  }

  HitRecord record;
  record.t = root;
  record.p = ray.at(record.t);
  Vec3 outwardNormal = (record.p - center) / radius;
  record.setFaceNormal(ray, outwardNormal);
  record.matPtr = matPtr.get();

  return record;
}

std::optional<HitRecord> HittableList::hit(Ray& ray) const {
  std::optional<HitRecord> result{std::nullopt};

  for (const auto& obj : objects) {
    if (auto record = obj->hit(ray)) {
      ray.setRayMax(record->t);
      result = record;
    }
  }

  return result;
}
