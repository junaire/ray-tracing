#include <fmt/format.h>

#include "color.h"
#include "vec3.h"

int main() {
  const int imageWigth = 256;
  const int imageHeight = 256;

  fmt::print("P3\n{} {}\n255\n", imageWigth, imageHeight);

  for (int j = imageHeight - 1; j >= 0; j--) {
    for (int i = imageHeight - 1; i >= 0; i--) {
      Color pixel{static_cast<double>(i) / (imageWigth - 1),
                  static_cast<double>(j) / (imageHeight - 1), 0.25};
	  writeColor(std::cout, pixel);

    }
  }
}

