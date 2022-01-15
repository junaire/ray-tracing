#pragma once
#include <climits>
#include <random>

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
inline double degreesToRadians(double degrees) { return degrees * kpi / 180.0; }
