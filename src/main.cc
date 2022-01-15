#include <fmt/format.h>

#include <cmath>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include "util.h"
#include "vec3.h"

Color rayColor(const Ray& ray, const Hittable& world, int depth) {
  if (depth <= 0) {
    return {0, 0, 0};
  }
  if (auto record = world.hit(ray, 0.001, kinfinity)) {
    Ray scattered;
    Color attenuation;
    if (record->matPtr->scatter(ray, *record, attenuation, scattered)) {
      return attenuation * rayColor(scattered, world, depth - 1);
    }
    return Color{0, 0, 0};
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

  auto ground = std::make_unique<Lambertian>(Color{0.8, 0.8, 0.0});
  auto center = std::make_unique<Lambertian>(Color{0.1, 0.2, 0.5});
  auto left = std::make_unique<Dielectric>(1.5);
  auto right = std::make_unique<Metal>(Color{0.8, 0.6, 0.2}, 0.0);

  world.add(
      std::make_unique<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, ground.get()));
  world.add(
      std::make_unique<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, center.get()));
  world.add(std::make_unique<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, left.get()));
  world.add(
      std::make_unique<Sphere>(Point3(-1.0, 0.0, -1.0), -0.4, left.get()));
  world.add(std::make_unique<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, right.get()));

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

