#include <fmt/format.h>

#include <cmath>

#include "color.h"
#include "ray.h"
#include "vec3.h"

double hitSphere(const Point3& center, double radius, const Ray& r) {
  Vec3 oc = r.origin() - center;
  auto a = dot(r.direction(), r.direction());
  auto halfb = dot(oc, r.direction());
  auto c = dot(oc, oc) - radius * radius;
  auto discriminant = halfb * halfb - 4 * a * c;
  if (discriminant < 0) {
    return -1.0;
  }
  return (-halfb - std::sqrt(discriminant)) / a;
}

Color rayColor(const Ray& ray) {
  // if in the sphere, change it's color.
  auto t = hitSphere(Point3(0, 0, -1), 0.5, ray);
  if (t > 0.0) {
    // gradient color
    Vec3 N = unitVector(ray.at(t) - Vec3{0, 0, -1});
    return 0.5 * Color{N.x() + 1, N.y() + 1, N.z() + 1};
  }
  Vec3 unitDirection = unitVector(ray.direction());

  t = 0.5 * (unitDirection.y() + 1.0);

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

