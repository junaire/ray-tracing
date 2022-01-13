#include "hittable_list.h"

std::optional<HitRecord> HittableList::hit(const Ray& ray, double tmin,
                                           double tmax) const {
  std::optional<HitRecord> result {std::nullopt};
  auto closest = tmax;

  for (const auto& obj : objects) {
    if (auto record = obj->hit(ray, tmin, closest)){
      closest = record->t;
	  result = record;
    }
  }

  return result;
}
