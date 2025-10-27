#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(static_cast<size_t>(-5)));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m1(3);
    int val = 1;
    for (size_t i = 0; i < m1.size(); ++i)
        for (size_t j = 0; j < m1.size(); ++j)
            m1[i][j] = val++;

    TDynamicMatrix<int> m2(m1);
    EXPECT_TRUE(m2 == m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    TDynamicMatrix<int> m2(m);
    m[0][0] = 9999;
    EXPECT_NE(m2[0][0], m[0][0]);
    EXPECT_EQ(2, m2[0][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);
    EXPECT_EQ((size_t)4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(3);
    m[1][2] = 42;
    EXPECT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(3);
    EXPECT_ANY_THROW(m[0].at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(3);
    EXPECT_ANY_THROW(m[0].at(m.size()));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    ASSERT_NO_THROW(m = m);
    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 5; m1[0][1] = 6;
    m1[1][0] = 7; m1[1][1] = 8;
    ASSERT_NO_THROW(m2 = m1);
    EXPECT_TRUE(m2 == m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(4);
    m2[0][0] = 11;
    m1 = m2;
    EXPECT_EQ((size_t)4, m1.size());
    EXPECT_EQ(11, m1[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(1), m2(3);
    m2[2][2] = 77;
    ASSERT_NO_THROW(m1 = m2);
    EXPECT_EQ((size_t)3, m1.size());
    EXPECT_EQ(77, m1[2][2]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(2), m2(2);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 2; ++j) {
            m1[i][j] = 5;
            m2[i][j] = 5;
        }
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(3);
    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(2), m2(3);
    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3; m1[1][1] = 4;
    m2[0][0] = 5; m2[0][1] = 6; m2[1][0] = 7; m2[1][1] = 8;
    TDynamicMatrix<int> sum = m1 + m2; // тут пусть результатом будет третья матрица :p
    EXPECT_EQ(6, sum[0][0]);
    EXPECT_EQ(8, sum[0][1]);
    EXPECT_EQ(10, sum[1][0]);
    EXPECT_EQ(12, sum[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    EXPECT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 5; m1[0][1] = 6; m1[1][0] = 7; m1[1][1] = 8;
    m2[0][0] = 1; m2[0][1] = 2; m2[1][0] = 3; m2[1][1] = 4;
    TDynamicMatrix<int> diff = m1 - m2;
    EXPECT_EQ(4, diff[0][0]);
    EXPECT_EQ(4, diff[0][1]);
    EXPECT_EQ(4, diff[1][0]);
    EXPECT_EQ(4, diff[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    EXPECT_ANY_THROW(m1 - m2);
}
