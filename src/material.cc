#include "material.h"

#include "util.h"

// Really bad code, needs refactor.
std::optional<ScatterResult> Lambertian::scatter(
    const Ray& ray, const HitRecord& record) const {
  auto scatterDirection = record.normal + randomUnitVector();

  if (scatterDirection.nearZero()) {
    scatterDirection = record.normal;
  }

  return ScatterResult{Ray{record.p, scatterDirection}, albedo};
}

std::optional<ScatterResult> Metal::scatter(const Ray& ray,
                                            const HitRecord& record) const {
  Vec3 reflected = reflect(unitVector(ray.direction()), record.normal);
  auto scattered = Ray{record.p, reflected + fuzz * randomInUnitSphere()};
  if (dot(scattered.direction(), record.normal) > 0) {
    return ScatterResult{std::move(scattered), albedo};
  }
  return std::nullopt;
}

std::optional<ScatterResult> Dielectric::scatter(
    const Ray& ray, const HitRecord& record) const {
  double refractionRatio = record.frontFace ? (1.0 / ir) : ir;
  Vec3 unitDirection = unitVector(ray.direction());

  double cosTheta = std::fmin(dot(-unitDirection, record.normal), 1.0);
  double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

  bool cannotRefract = refractionRatio * sinTheta > 1.0;

  Vec3 direction;
  if (cannotRefract ||
      reflectance(cosTheta, refractionRatio) > randomDouble()) {
    direction = reflect(unitDirection, record.normal);
  } else {
    direction = refract(unitDirection, record.normal, refractionRatio);
  }

  return ScatterResult{Ray{record.p, direction}, Color{1.0, 1.0, 1.0}};
}

double Dielectric::reflectance(double cosine, double refIdx) {
  auto r0 = (1 - refIdx) / (1 + refIdx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}
