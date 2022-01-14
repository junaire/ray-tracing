#include <fmt/format.h>

#include <cmath>

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "util.h"
#include "vec3.h"

Color rayColor(const Ray& ray, const Hittable& world, int depth) {
  if (depth <= 0) {
    return {0, 0, 0};
  }
  if (auto record = world.hit(ray, 0, kinfinity)) {
    Point3 target = record->p + randomInHemiSPhere(record->normal);
    return 0.5 * rayColor(Ray{record->p, target - record->p}, world, depth - 1);
  }

  Vec3 unitDirection = unitVector(ray.direction());
  auto t = 0.5 * (unitDirection.y() + 1.0);
  // our beautiful background.
  return (1.0 - t) * Color{1.0, 1.0, 1.0} + t * Color{0.5, 0.7, 1.0};
}

int main() {
  // image
  constexpr auto aspectRadio = 16.0 / 9.0;
  constexpr int imageWigth = 400;
  constexpr int imageHeight = static_cast<int>(imageWigth / aspectRadio);
  constexpr int samplePerPixel = 100;
  constexpr int maxDepth = 50;

  // world
  HittableList world;
  world.add(std::make_unique<Sphere>(Point3(0, 0, -1), 0.5));
  world.add(std::make_unique<Sphere>(Point3(0, -100.5, -1), 100));

  // camera
  Camera camera;

  // render
  fmt::print("P3\n{} {}\n255\n", imageWigth, imageHeight);

  for (int j = imageHeight - 1; j >= 0; --j) {
    for (int i = 0; i < imageWigth; ++i) {
      Color pixelColor{0, 0, 0};
      for (int s = 0; s < samplePerPixel; ++s) {
        auto u = (i + randomDouble()) / (imageWigth - 1);
        auto v = (j + randomDouble()) / (imageHeight - 1);

        Ray ray = camera.getRay(u, v);
        pixelColor += rayColor(ray, world, maxDepth);
      }
      writeColor(std::cout, pixelColor, samplePerPixel);
    }
  }
}

