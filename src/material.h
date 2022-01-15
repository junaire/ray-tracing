#pragma once

#include "hittable.h"
#include "vec3.h"

class Material {
 public:
  virtual bool scatter(const Ray& ray, const HitRecord& record,
                       Color& attenuation, Ray& scattered) const = 0;
  virtual ~Material() = default;
};

class Lambertian : public Material {
 public:
  explicit Lambertian(const Color& color) : albedo(color) {}

  bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation,
               Ray& scattered) const override;

 private:
  Color albedo;
};

class Metal : public Material {
 public:
  Metal(const Color& color, double fuzzy)
      : albedo(color), fuzz(fuzzy < 1 ? fuzzy : 1) {}

  bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation,
               Ray& scattered) const override;

 private:
  Color albedo;
  double fuzz;
};

class Dielectric : public Material {
 public:
  explicit Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

  bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation,
               Ray& scattered) const override;

 private:
  static double reflectance(double cosine, double refIdx);
  double ir;
};
