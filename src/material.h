#pragma once

#include <optional>

#include "hittable.h"
#include "vec3.h"

struct ScatterResult {
  ScatterResult(Ray ray, Color color)
      : scattered(std::move(ray)), attenuation(std::move(color)) {}

  Ray scattered;
  Color attenuation;
};

class Material {
 public:
  [[nodiscard]] virtual std::optional<ScatterResult> scatter(
      const Ray& ray, const HitRecord& record) const = 0;
  virtual ~Material() = default;
};

class Lambertian : public Material {
 public:
  explicit Lambertian(const Color& color) : albedo(color) {}

  [[nodiscard]] std::optional<ScatterResult> scatter(
      const Ray& ray, const HitRecord& record) const override;

 private:
  Color albedo;
};

class Metal : public Material {
 public:
  Metal(const Color& color, double fuzzy)
      : albedo(color), fuzz(fuzzy < 1 ? fuzzy : 1) {}

  [[nodiscard]] std::optional<ScatterResult> scatter(
      const Ray& ray, const HitRecord& record) const override;

 private:
  Color albedo;
  double fuzz;
};

class Dielectric : public Material {
 public:
  explicit Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

  [[nodiscard]] std::optional<ScatterResult> scatter(
      const Ray& ray, const HitRecord& record) const override;

 private:
  static double reflectance(double cosine, double refIdx);
  double ir;
};
