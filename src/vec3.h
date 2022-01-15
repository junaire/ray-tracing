#pragma once

#include <cmath>
#include <iostream>

#include "util.h"

class Vec3 {
 public:
  double e[3];

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
};

using Point3 = Vec3;
using Color = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline constexpr Vec3 operator+(const Vec3& u, const Vec3& v) {
  return {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]};
}

inline constexpr Vec3 operator-(const Vec3& u, const Vec3& v) {
  return {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]};
}

inline constexpr Vec3 operator*(const Vec3& u, const Vec3& v) {
  return {u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]};
}

inline constexpr Vec3 operator*(const Vec3& v, double t) {
  return {t * v.e[0], t * v.e[1], t * v.e[2]};
}

inline constexpr Vec3 operator*(double t, const Vec3& v) { return v * t; }

inline constexpr Vec3 operator/(const Vec3& v, double t) { return (1 / t) * v; }

inline constexpr double dot(const Vec3& u, const Vec3& v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline constexpr Vec3 cross(const Vec3& u, const Vec3& v) {
  return {
      u.e[1] * v.e[2] - u.e[2] * v.e[1],
      u.e[2] * v.e[0] - u.e[0] * v.e[2],
      u.e[0] * v.e[1] - u.e[1] * v.e[0],
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
