#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

// Fills a 3x5 Matrix with a value and checks
// that Matrix_print outputs the correct header and that each element
//appears with the expected spaces/newlines
TEST(test_matrix_print) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, value);

  std::ostringstream expected;
  expected << width << " " << height << "\n"
           << "42 42 42 \n"
           << "42 42 42 \n"
           << "42 42 42 \n"
           << "42 42 42 \n"
           << "42 42 42 \n";

  std::ostringstream actual;
  Matrix_print(&mat, actual);

  ASSERT_EQUAL(expected.str(), actual.str());
}

// Fills a 3x5 Matrix with a value and checks
// that Matrix_width returns the correct width of the matrix
TEST(test_matrix_width) {
  Matrix mat; 
  const int width = 3;
  const int height = 5;

  Matrix_init(&mat, width, height);

  ASSERT_EQUAL(Matrix_width(&mat), width);
}

// Fills a 3x5 Matrix with a value and checks
// that Matrix_height returns the correct height of the matrix
TEST(test_matrix_height) {
  Matrix mat; 
  const int width = 3;
  const int height = 5;

  Matrix_init(&mat, width, height);

  ASSERT_EQUAL(Matrix_height(&mat), height);
}


//Fills the border of a 3x5 Matrix with a value and checks
//that the border elements are changed but not the interior elements
TEST(test_fill_border) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int border_value = 2;
  const int interior_value = 1;

  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, interior_value);
  Matrix_fill_border(&mat, border_value);

  for (int r = 0; r < height; ++r){
    for (int c = 0; c < width; ++c){
      if (r==0 || r == height -1){
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), border_value);
      }else if(c == 0 || c == width -1){
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), border_value);
      }else{
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), interior_value);
      }
    }
  }
}

// Fills a 2x3 Matrix with a value and checks
// that Matrix_max returns the correct greatest value of the matrix
TEST(test_matrix_max) {
  Matrix mat; 
  const int width = 3;
  const int height = 2;

  Matrix_init(&mat, width, height);

  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = -7;
  *Matrix_at(&mat, 0, 2) = 3;

  *Matrix_at(&mat, 1, 0) = 6;
  *Matrix_at(&mat, 1, 1) = 5;
  *Matrix_at(&mat, 1, 2) = 6;

  ASSERT_EQUAL(Matrix_max(&mat), 6);
}

// Fills a 2x3 Matrix with a value and checks
// that Matrix_column_of_min_value_in_row returns the correct column 
//containing the minimum value of the matrix given a specific region
TEST(test_column_of_min_value) {
  Matrix mat; 
  const int width = 3;
  const int height = 2;

  Matrix_init(&mat, width, height);

  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = -7;
  *Matrix_at(&mat, 0, 2) = 3;

  *Matrix_at(&mat, 1, 0) = 6;
  *Matrix_at(&mat, 1, 1) = 5;
  *Matrix_at(&mat, 1, 2) = 6;

  int result = Matrix_column_of_min_value_in_row(&mat, 0, 0, 3);


  ASSERT_EQUAL(result, 1);
}

//Fills a 4x1 Matrix with values and checks
//that Matrix_column_of_min_value_in_row returns the leftmost column
//when there is a tie for the minimum value
TEST(test_column_of_min_value_tie_leftmost){
  Matrix mat;
  Matrix_init(&mat, 4, 1);

  *Matrix_at(&mat, 0,0) = 5;
  *Matrix_at(&mat, 0,1) = -1;
  *Matrix_at(&mat, 0,2) = -1;
  *Matrix_at(&mat, 0,3) = 4;

  int result = Matrix_column_of_min_value_in_row(&mat, 0, 0, 4);

  ASSERT_EQUAL(result, 1);
}

//Fills a 4x1 Matrix with values and checks
//that Matrix_column_of_min_value_in_row returns the column
//with the min value
TEST(test_column_of_min_value_left_edge_case){
  Matrix mat;
  Matrix_init(&mat, 4, 1);

  *Matrix_at(&mat, 0,0) = -5;
  *Matrix_at(&mat, 0,1) = -1;
  *Matrix_at(&mat, 0,2) = -1;
  *Matrix_at(&mat, 0,3) = 4;

  int result = Matrix_column_of_min_value_in_row(&mat, 0, 0, 4);

  ASSERT_EQUAL(result, 0);
}


//Fills a 4x1 Matrix with values and checks
//that Matrix_column_of_min_value_in_row returns the column
//with the min value
TEST(test_column_of_min_value_right_edge_case){
  Matrix mat;
  Matrix_init(&mat, 4, 1);

  *Matrix_at(&mat, 0,0) = 5;
  *Matrix_at(&mat, 0,1) = -1;
  *Matrix_at(&mat, 0,2) = -1;
  *Matrix_at(&mat, 0,3) = -4;

  int result = Matrix_column_of_min_value_in_row(&mat, 0, 0, 4);

  ASSERT_EQUAL(result, 3);
}


//Fills a 4x1 Matrix with values and checks
//that Matrix_column_of_min_value_in_row returns the column
//with the min value in a subrange
TEST(test_column_of_min_value_subrange){
  Matrix mat;
  Matrix_init(&mat, 5, 1);

  *Matrix_at(&mat, 0,0) = -5;
  *Matrix_at(&mat, 0,1) = -1;
  *Matrix_at(&mat, 0,2) = -1;
  *Matrix_at(&mat, 0,3) = -4;
  *Matrix_at(&mat, 0,4) = -9;

  int result = Matrix_column_of_min_value_in_row(&mat, 0, 1, 4);

  ASSERT_EQUAL(result, 3);
}

// Fills a 2x3 Matrix with a value and checks
// that Matrix_min_value_in_row returns the correct minimum value 
//in a given row
TEST(test_min_value_in_row) {
  Matrix mat; 
  const int width = 3;
  const int height = 2;

  Matrix_init(&mat, width, height);

  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = -7;
  *Matrix_at(&mat, 0, 2) = 3;

  *Matrix_at(&mat, 1, 0) = 6;
  *Matrix_at(&mat, 1, 1) = 5;
  *Matrix_at(&mat, 1, 2) = 6;

  int result = Matrix_min_value_in_row(&mat, 0, 0, 3);


  ASSERT_EQUAL(result, -7);
}



TEST_MAIN() // Do NOT put a semicolon here