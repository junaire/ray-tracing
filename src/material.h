#pragma once

#include "hittable.h"
#include "vec3.h"

class Material {
 public:
  virtual bool scatter(const Ray& ray, const HitRecord& record,
                       Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
 public:
  Color albedo;
  explicit Lambertian(const Color& color) : albedo(color) {}

  bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation,
               Ray& scattered) const override;
};

class Metal : public Material {
 public:
  Color albedo;
  double fuzz;

  Metal(const Color& color, double fuzzy)
      : albedo(color), fuzz(fuzzy < 1 ? fuzzy : 1) {}

  bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation,
               Ray& scattered) const override;
};

class Dielectric : public Material {
 public:
  double ir;

  explicit Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

  bool scatter(const Ray& ray, const HitRecord& record, Color& attenuation,
               Ray& scattered) const override;

 private:
  static double reflectance(double cosine, double refIdx);
};
