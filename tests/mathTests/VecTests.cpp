#include <gtest/gtest.h>
#include "Vec.h"

TEST(vector_tests, cross_product) {
    Vec v1 = Vec(1, 2, 3);
    Vec v2 = Vec(4, 5, 6);

    EXPECT_EQ(Vec(-3, 6, -3), v1 ^ v2);
}

TEST(vector_tests, dot_product) {
    Vec v1 = Vec(1, 2, 3);
    Vec v2 = Vec(4, 5, 6);

    EXPECT_EQ(32, v1 * v2);
}

TEST(vector_tests, scale_vector) {
    double s = 2;
    Vec v = Vec(1, 2, 3);

    EXPECT_EQ(Vec(2, 4, 6), s * v);
}

TEST(vector_tests, normalize_vector) {
    Vec v = Vec(5, 0, 0);

    EXPECT_EQ(Vec(1, 0, 0), v.normalize());
}

TEST(vector_tests, length_vector) {
    Vec v = Vec(5, 0, 0);

    EXPECT_EQ(5, v.length());
}

TEST(vector_tests, add_vectors) {
    Vec v1 = Vec(1, 2, 3);
    Vec v2 = Vec(4, 5, 6);

    EXPECT_EQ(Vec(5, 7, 9), v1 + v2);
}

TEST(vector_tests, subtract_vectors) {
    Vec v1 = Vec(1, 2, 3);
    Vec v2 = Vec(4, 5, 6);

    EXPECT_EQ(Vec(-3, -3, -3), v1 - v2);
}
