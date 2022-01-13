#include <fmt/format.h>

#include "color.h"
#include "ray.h"
#include "vec3.h"

Color rayColor(const Ray& ray) {
  Vec3 unitDirection = unitVector(ray.direction());
  auto t = 0.5 * (unitDirection.y() + 1.0);

  return ((1.0 - t) * Color{1.0, 1.0, 1.0}) + (t * Color{0.5, 0.7, 1.0});
}

int main() {
  // image
  constexpr auto aspectRadio = 16.0 / 9.0;
  constexpr int imageWigth = 400;
  constexpr int imageHeight = static_cast<int>(imageWigth / aspectRadio);

  // camera
  constexpr auto viewportHeight = 2.0;
  constexpr auto viewportWidth = aspectRadio * viewportHeight;
  constexpr auto focalLength = 1.0;

  constexpr Point3 origin{0, 0, 0};
  constexpr Vec3 horizontal{viewportWidth, 0, 0};
  constexpr Vec3 vertical{0, viewportHeight, 0};

  constexpr auto lowerLeftCorner =
      origin - (horizontal / 2) - (vertical / 2) - Vec3{0, 0, focalLength};

  // render
  fmt::print("P3\n{} {}\n255\n", imageWigth, imageHeight);

  for (int j = imageHeight - 1; j >= 0; --j) {
    for (int i = 0; i < imageWigth; ++i) {
      auto u = static_cast<double>(i) / (imageWigth - 1);
      auto v = static_cast<double>(j) / (imageHeight - 1);

      Ray r{origin,
            lowerLeftCorner + (u * horizontal) + (v * vertical) - origin};

      writeColor(std::cout, rayColor(r));
    }
  }
}

