#include "tmatrix.h"
#include <gtest.h>

void Fill(TDynamicMatrix<int>& m, size_t n)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            m[i][j] = i * n + j;
}

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
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_zero_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(0));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(4);
    Fill(m, 4);
    TDynamicMatrix<int> m1(m);
    EXPECT_TRUE(m1 == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(3);
    Fill(m, 3);
    TDynamicMatrix<int> m1(m);
    m1[0][0] = 100;
    EXPECT_EQ(0, m[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);
    EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(4);
    m[1][2] = 7;
    EXPECT_EQ(7, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(4);
    ASSERT_ANY_THROW(m.at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(4);
    ASSERT_ANY_THROW(m.at(4));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(3);
    Fill(m, 3);
    TDynamicMatrix<int>& r = m;
    ASSERT_NO_THROW(m = r);
    EXPECT_EQ(3, m.size());
    EXPECT_EQ(8, m[2][2]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(3);
    Fill(m2, 3);
    m1 = m2;
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(3), m2(5);
    m1 = m2;
    EXPECT_EQ(5, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(3), m2(5);
    Fill(m2, 5);
    ASSERT_NO_THROW(m1 = m2);
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(3), m2(3);
    Fill(m1, 3);
    Fill(m2, 3);
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(3);
    Fill(m, 3);
    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(3), m2(4);
    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(3);
    Fill(m1, 3);
    Fill(m2, 3);
    TDynamicMatrix<int> res = m1 + m2;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            EXPECT_EQ(2 * m1[i][j], res[i][j]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(4);
    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(3);
    Fill(m1, 3);
    Fill(m2, 3);
    TDynamicMatrix<int> res = m1 - m2;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            EXPECT_EQ(0, res[i][j]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(4);
    ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
    TDynamicMatrix<int> m(3);
    Fill(m, 3);
    TDynamicMatrix<int> res = m * 2;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            EXPECT_EQ(2 * m[i][j], res[i][j]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    TDynamicVector<int> v(2);
    v[0] = 5; v[1] = 6;
    TDynamicVector<int> res = m * v;
    EXPECT_EQ(2, res.size());
    EXPECT_EQ(17, res[0]);
    EXPECT_EQ(39, res[1]); 
    // [1 2]   [5]   [1*5 + 2*6]   [17]
    // [3 4] * [6] = [3*5 + 4*6] = [39]
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
    TDynamicMatrix<int> m(3);
    TDynamicVector<int> v(2);
    ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;
    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;
    TDynamicMatrix<int> res = m1 * m2;
    EXPECT_EQ(19, res[0][0]);
    EXPECT_EQ(22, res[0][1]);
    EXPECT_EQ(43, res[1][0]);
    EXPECT_EQ(50, res[1][1]);
    // [1 2]   [5 6]   [19 22]
    // [3 4] * [7 8] = [43 50]
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(4);
    ASSERT_ANY_THROW(m1 * m2);
}

