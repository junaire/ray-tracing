#include <fmt/format.h>

#include <climits>
#include <cmath>
#include <random>

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

static constexpr double kinfinity = std::numeric_limits<double>::infinity();
static constexpr double kpi = 3.14159265358979323846;

inline double randomDouble() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

inline double randomDouble(double min, double max) {
  return min + (max - min) * randomDouble();
}
Color rayColor(const Ray& ray, const Hittable *world) {
  if (auto record = world->hit(ray, 0, kinfinity)) {
    return 0.5 * (record->normal + Color{1, 1, 1});
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

  // world
  auto world = std::make_unique<HittableList>();
  world->add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world->add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

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
        pixelColor += rayColor(ray, world.get());
      }
      writeColor(std::cout, pixelColor, samplePerPixel);
    }
  }
}

