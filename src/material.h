#pragma once

#include "hittable.h"
#include "vec3.h"

class Material {
 public:
  virtual bool scatter(const Ray& ray, const HitRecord& record,
                       Color& attenuation, Ray& scattered) const = 0;
};
