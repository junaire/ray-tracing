#include <fmt/format.h>

#include <cmath>

#include "camera.h"
#include "color.h"
#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "util.h"
#include "vec3.h"

Color rayColor(const Ray& ray, const Hittable& world, int depth) {
  if (depth <= 0) {
    return {0, 0, 0};
  }
  if (auto record = world.hit(ray, 0.001, kinfinity)) {
    if (auto scatterResult = record->matPtr->scatter(ray, *record)) {
      return scatterResult->attenuation *
             rayColor(scatterResult->scattered, world, depth - 1);
    }
    return Color{0, 0, 0};
  }

  Vec3 unitDirection = unitVector(ray.direction());
  auto t = 0.5 * (unitDirection.y() + 1.0);
  // our beautiful background.
  return (1.0 - t) * Color{1.0, 1.0, 1.0} + t * Color{0.5, 0.7, 1.0};
}

HittableList generateScene() {
  // world
  HittableList world;
  std::shared_ptr<Material> material;

  auto ground = std::make_shared<Lambertian>(Color{0.5, 0.5, 0.5});
  world.add(std::make_unique<Sphere>(Point3(0.0, -1000.0, 0.0), 1000.0,
                                     ground));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      auto chooseMat = randomDouble();
      Point3 center{a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble()};

      if ((center - Point3{4, 0.2, 0}).length() > 0.9) {
        if (chooseMat < 0.8) {
          auto albedo = Color::random() * Color::random();
          material = std::make_shared<Lambertian>(albedo);
          world.add(std::make_unique<Sphere>(center, 0.2, material));
        } else if (chooseMat < 0.95) {
          auto albedo = Color::random(0.5, 1);
          auto fuzz = randomDouble(0, 0.5);
          material = std::make_shared<Metal>(albedo, fuzz);
          world.add(std::make_unique<Sphere>(center, 0.2, material));

        } else {
          material = std::make_shared<Dielectric>(1.5);
          world.add(std::make_unique<Sphere>(center, 0.2, material));
        }
      }
    }
  }
  auto material1 = std::make_shared<Dielectric>(1.5);
  world.add(std::make_unique<Sphere>(Point3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
  world.add(std::make_unique<Sphere>(Point3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
  world.add(std::make_unique<Sphere>(Point3(4, 1, 0), 1.0, material3));

  return world;
}

int main() {
  // image
  constexpr auto aspectRadio = 16.0 / 9.0;
  constexpr int imageWigth = 1200;
  constexpr int imageHeight = static_cast<int>(imageWigth / aspectRadio);
  constexpr int samplePerPixel = 10;
  constexpr int maxDepth = 50;

  auto world = generateScene();


  // camera
  Camera camera(Point3{13, 2, 3}, Point3{0, 0, 0}, Vec3{0, 1, 0}, 20,
                aspectRadio, 0.1, 10.0);

  // render
  fmt::print("P3\n{} {}\n255\n", imageWigth, imageHeight);

  for (int j = imageHeight - 1; j >= 0; --j) {
    std::cerr << "lines remaining " << j << "\n";
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

