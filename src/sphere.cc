#include "sphere.h"

#include <cmath>

std::optional<HitRecord> Sphere::hit(const Ray& ray, double tmin,
                                     double tmax) const {
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
  if (root < tmin || root > tmax) {
    root = (-halfb + sqrtd) / a;
    if (root < tmin || root > tmax) {
      return std::nullopt;
    }
  }

  HitRecord record;
  record.t = root;
  record.p = ray.at(record.t);
  Vec3 outwardNormal = (record.p - center) / radius;
  record.setFaceNormal(ray, outwardNormal);

  return record;
}
