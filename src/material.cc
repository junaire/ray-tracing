#include "material.h"

#include "util.h"

// Really bad code, needs refactor.
bool Lambertian::scatter(const Ray& ray, const HitRecord& record,
                         Color& attenuation, Ray& scattered) const {
  auto scatterDirection = record.normal + randomUnitVector();

  if (scatterDirection.nearZero()) {
    scatterDirection = record.normal;
  }

  scattered = Ray{record.p, scatterDirection};
  attenuation = albedo;

  return true;
}

bool Metal::scatter(const Ray& ray, const HitRecord& record, Color& attenuation,
                    Ray& scattered) const {
  Vec3 reflected = reflect(unitVector(ray.direction()), record.normal);
  scattered = Ray{record.p, reflected + fuzz * randomInUnitSphere()};
  attenuation = albedo;
  return dot(scattered.direction(), record.normal) > 0;
}

bool Dielectric::scatter(const Ray& ray, const HitRecord& record,
                         Color& attenuation, Ray& scattered) const {
  attenuation = Color{1.0, 1.0, 1.0};
  double refractionRatio = record.frontFace ? (1.0 / ir) : ir;
  Vec3 unitDirection = unitVector(ray.direction());

  double cosTheta = std::fmin(dot(-unitDirection, record.normal), 0);
  double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

  bool cannotRefract = refractionRatio * sinTheta > 1.0;

  Vec3 direction;
  if (cannotRefract ||
      reflectance(cosTheta, refractionRatio) > randomDouble()) {
    direction = reflect(unitDirection, record.normal);
  } else {
    direction = refract(unitDirection, record.normal, refractionRatio);
  }

  scattered = Ray{record.p, direction};
  return true;
}

double Dielectric::reflectance(double cosine, double refIdx) {
  auto r0 = (1 - refIdx) / (1 + refIdx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}
