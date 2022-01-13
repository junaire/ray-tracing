#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

class HittableList : public Hittable {
 public:
  std::vector<std::shared_ptr<Hittable>> objects;

  HittableList() = default;
  explicit HittableList(std::shared_ptr<Hittable> obj) { add(std::move(obj)); }

  void add(std::shared_ptr<Hittable> obj) { objects.push_back(std::move(obj)); }

  void clear() { objects.clear(); }

  [[nodiscard]] std::optional<HitRecord> hit(const Ray& ray, double tmin,
                                             double tmax) const override;
};
