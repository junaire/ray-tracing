#pragma once
#include <fmt/format.h>

#include <cmath>

class Vec3 {
   double e[3];

  friend Vec3 operator+(const Vec3& u, const Vec3& v);
  friend Vec3 operator-(const Vec3& u, const Vec3& v);
  friend Vec3 operator*(const Vec3& u, double v);
  friend Vec3 operator/(const Vec3& u, double v);
  friend double dot(const Vec3& u, const Vec3& v);
  friend Vec3 cross(const Vec3& u, const Vec3& v);

 public:
  constexpr Vec3() : e{0, 0, 0} {}
  constexpr Vec3(double c0, double c1, double c2) : e{c0, c1, c2} {}

  constexpr double x() const { return e[0]; }
  constexpr double y() const { return e[1]; }
  constexpr double z() const { return e[2]; }

  constexpr Vec3 operator-() const { return Vec3{-e[0], -e[1], -e[2]}; }
  constexpr double operator[](int i) const { return e[i]; }
  constexpr double& operator[](int i) { return e[i]; }

  // TODO(Jun): use swap idiom
  constexpr Vec3& operator+=(const Vec3& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
  }
  constexpr Vec3& operator*=(double v) {
    e[0] *= v;
    e[1] *= v;
    e[2] *= v;
    return *this;
  }
  constexpr Vec3& operator/=(double v) {
    e[0] /= v;
    e[1] /= v;
    e[2] /= v;
    return *this;
  }

  constexpr double lengthSquared() const { return e[0] + e[1] + e[2]; }

  constexpr double length() const { return std::sqrt(lengthSquared()); }
};

Vec3 operator+(const Vec3& u, const Vec3& v) {
  return Vec3{u.e[0] + v.e[0], u.e[1] + v.e[1], v.e[2] + v.e[2]};
}

Vec3 operator-(const Vec3& u, const Vec3& v) {
  return Vec3{u.e[0] - v.e[0], u.e[1] - v.e[1], v.e[2] - v.e[2]};
}

Vec3 operator*(const Vec3& u, double v) {
  return Vec3{u.e[0] * v, u.e[1] * v, u.e[2] * v};
}

Vec3 operator/(const Vec3& u, double v) { return u * (1 / v); }

double dot(const Vec3& u, const Vec3& v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + v.e[2] * v.e[2];
}

Vec3 cross(const Vec3& u, const Vec3& v) {
  return Vec3{
      u.e[1] * v.e[2] - u.e[2] * v.e[1],
      u.e[2] * v.e[0] - u.e[0] * v.e[2],
      u.e[0] * v.e[1] - u.e[1] * v.e[0],
  };
}

Vec3 unitVector(Vec3 v) { return v / v.length(); }
using Point3 = Vec3;
using Color = Vec3;
