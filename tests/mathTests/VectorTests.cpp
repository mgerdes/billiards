#include <gtest/gtest.h>
#include "Matrix.h"
#include "Vector.h"

TEST(vector_tests, cross_product) {
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(4, 5, 6);

    EXPECT_EQ(Vector(-3, 6, -3), v1 ^ v2);
}

TEST(vector_tests, dot_product) {
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(4, 5, 6);

    EXPECT_EQ(32, v1 * v2);
}

TEST(vector_tests, scale_vector) {
    double s = 2;
    Vector v = Vector(1, 2, 3);

    EXPECT_EQ(Vector(2, 4, 6), s * v);
}

TEST(vector_tests, normalize_vector) {
    Vector v = Vector(5, 0, 0);

    EXPECT_EQ(Vector(1, 0, 0), v.normalize());
}

TEST(vector_tests, length_vector) {
    Vector v = Vector(5, 0, 0);

    EXPECT_EQ(5, v.length());
}

TEST(vector_tests, add_vectors) {
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(4, 5, 6);

    EXPECT_EQ(Vector(5, 7, 9), v1 + v2);
}

TEST(vector_tests, subtract_vectors) {
    Vector v1 = Vector(1, 2, 3);
    Vector v2 = Vector(4, 5, 6);

    EXPECT_EQ(Vector(-3, -3, -3), v1 - v2);
}

TEST(vector_tests, matrix_times_vector) {
    Matrix m = Matrix(1, 0, 0, 4,
                      0, 2, 0, 5,
                      0, 0, 3, 6,
                      0, 0, 0, 0);
    Vector v = Vector(1, 2, 3);

    EXPECT_EQ(Vector(5, 9, 15), m * v);
}

TEST(vector_tests, rotate_vector) {
    Vector v = Vector(0, 1, 0);
    Vector axis = Vector(0, 0, 1);

    EXPECT_EQ(Vector(1, 0, 0), v.rotate(axis, M_PI/2));
}
