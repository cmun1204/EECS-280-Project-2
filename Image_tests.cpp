#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST(test_image_init) {
  Image img;
  const Pixel black = {0, 0, 0};

  Image_init(&img, 2, 2);

  ASSERT_EQUAL(Image_width(&img), 2);
  ASSERT_EQUAL(Image_height(&img), 2);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 1), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 0), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 1), black));
}

TEST(test_image_init_PPM) {
Image img;

  std::istringstream ppm(
    "P3\n"
    "2 2\n"
    "255\n"
    "0 0 0   255 0 0\n"
    "0 255 0 0 0 255\n"
  );

  Image_init(&img, ppm);

  ASSERT_EQUAL(Image_width(&img), 2);
  ASSERT_EQUAL(Image_height(&img), 2);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), Pixel{0, 0, 0}));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 1), Pixel{255, 0, 0}));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 0), Pixel{0, 255, 0}));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 1), Pixel{0, 0, 255}));
}

TEST(test_image_width) {
  Image img;
  Image_init(&img, 5, 6);
  int test_width = 5;

  ASSERT_EQUAL(Image_width(&img), test_width);
}

TEST(test_image_height) {
 Image img;
  Image_init(&img, 5, 6);
  int test_height = 6;

  ASSERT_EQUAL(Image_height(&img), test_height);
}

TEST(test_image_set_pixel) {
  Image img;
  const Pixel blue = {0, 0, 255};
  const Pixel red = {255, 0, 0};
  const Pixel black = {0, 0, 0};

  Image_init(&img, 3, 3);

  Image_set_pixel(&img, 2, 2, blue);
  Image_set_pixel(&img, 1, 1, red);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 2, 2), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 1), red));

  //check other pixels to ensure not changed
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 2), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 2, 1), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 2), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 2, 0), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 0), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 1), black));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), black));
}

TEST(test_image_get_pixel) {
  Image img;
  const Pixel black = {0,0,0};

  Image_init(&img, 2, 2);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), black));
}

TEST(test_image_fill) {
  Image img;
  const Pixel white = {255, 255, 255};

  int height = 3;
  int width = 3;

  Image_init(&img, width, height);

  Image_fill(&img, white);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, i, j), white));
    }
  }
}

TEST_MAIN() // Do NOT put a semicolon here
