#include <gtest/gtest.h>
#include "Matrix.h"
#include "Vector.h"

TEST(matrix_tests, matrix_times_matrix) {
    Matrix m1 = Matrix(1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 10, 11, 12,
                       13, 14, 15, 16);
    Matrix m2 = Matrix(17, 18, 19, 20,
                       21, 22, 23, 24,
                       25, 26, 27, 28,
                       29, 30, 31, 32);

    EXPECT_EQ(m1 * m2, Matrix(250, 260, 270, 280,
                              618, 644, 670, 696,
                              986, 1028, 1070, 1112,
                              1354, 1412, 1470, 1528));
}

