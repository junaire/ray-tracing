#pragma once

#include <cmath>

#include "util.h"

class Vec3 {
 public:
  constexpr Vec3() : e{0, 0, 0} {}
  constexpr Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  static Vec3 random() {
    return {randomDouble(), randomDouble(), randomDouble()};
  }

  static Vec3 random(double min, double max) {
    return {randomDouble(min, max), randomDouble(min, max),
            randomDouble(min, max)};
  }

  [[nodiscard]] bool nearZero() const {
    const auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
           (std::fabs(e[2]) < s);
  }

  [[nodiscard]] constexpr double x() const { return e[0]; }
  [[nodiscard]] constexpr double y() const { return e[1]; }
  [[nodiscard]] constexpr double z() const { return e[2]; }

  constexpr Vec3 operator-() const { return {-e[0], -e[1], -e[2]}; }
  constexpr double operator[](int i) const { return e[i]; }
  constexpr double& operator[](int i) { return e[i]; }

  constexpr Vec3& operator+=(const Vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }

  constexpr Vec3& operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  constexpr Vec3& operator/=(const double t) { return *this *= 1 / t; }

  [[nodiscard]] constexpr double lengthSquared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  [[nodiscard]] constexpr double length() const {
    return std::sqrt(lengthSquared());
  }

 private:
  double e[3];
};

using Point3 = Vec3;
using Color = Vec3;

inline constexpr Vec3 operator+(const Vec3& u, const Vec3& v) {
  return {u.x() + v.x(), u.y() + v.y(), u.z() + v.z()};
}

inline constexpr Vec3 operator-(const Vec3& u, const Vec3& v) {
  return {u.x() - v.x(), u.y() - v.y(), u.z() - v.z()};
}

inline constexpr Vec3 operator*(const Vec3& u, const Vec3& v) {
  return {u.x() * v.x(), u.y() * v.y(), u.z() * v.z()};
}

inline constexpr Vec3 operator*(const Vec3& v, double t) {
  return {t * v.x(), t * v.y(), t * v.z()};
}

inline constexpr Vec3 operator*(double t, const Vec3& v) { return v * t; }

inline constexpr Vec3 operator/(const Vec3& v, double t) { return (1 / t) * v; }

inline constexpr double dot(const Vec3& u, const Vec3& v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline constexpr Vec3 cross(const Vec3& u, const Vec3& v) {
  return {
      u.y() * v.z() - u.z() * v.y(),
      u.z() * v.x() - u.x() * v.z(),
      u.x() * v.y() - u.y() * v.x(),
  };
}

inline constexpr Vec3 unitVector(const Vec3& v) { return v / v.length(); }

inline Vec3 randomInUnitSphere() {
  while (true) {
    auto p = Vec3::random(-1, 1);
    if (p.lengthSquared() >= 1) {
      continue;
    }
    return p;
  }
}

inline Vec3 randomUnitVector() { return unitVector(randomInUnitSphere()); }

inline Vec3 reflect(const Vec3& v, const Vec3& n) {
  return v - (2 * dot(v, n) * n);
}

inline Vec3 refract(const Vec3& uv, const Vec3& n, double eat) {
  auto cosTheta = std::fmin(dot(-uv, n), 1.0);
  Vec3 rOutPerp = eat * (uv + cosTheta * n);
  Vec3 rOutParrallel =
      -std::sqrt(std::fabs(1.0 - rOutPerp.lengthSquared())) * n;
  return rOutPerp + rOutParrallel;
}

inline Vec3 randomInUnitDisk() {
  while (true) {
    auto p = Vec3{randomDouble(-1, 1), randomDouble(-1, 1), 0};
    if (p.lengthSquared() >= 1) {
      continue;
    }
    return p;
  }
}
