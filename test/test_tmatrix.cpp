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
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	m[0][0] = 10;
	m[2][3] = 25;
	TDynamicMatrix<int> m1(m);

	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	m[1][1] = 7;
	TDynamicMatrix<int> m1(m);
	m1[1][1] = 99;

	EXPECT_EQ(7, m[1][1]);
	EXPECT_EQ(99, m1[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(4);

	EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[1][2] = 15;
	m[4][0] = 8;

	EXPECT_EQ(15, m[1][2]);
	EXPECT_EQ(8, m[4][0]);
	EXPECT_EQ(0, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);

	ASSERT_ANY_THROW(m.at(-1).at(0));
	ASSERT_ANY_THROW(m.at(0).at(-1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);

	ASSERT_ANY_THROW(m.at(5).at(0));
	ASSERT_ANY_THROW(m.at(0).at(5));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	m[2][2] = 12;

	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(12, m[2][2]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(5), m2(5);
	m1[1][3] = 42;
	m2 = m1;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(3), m2(7);
	m1[0][1] = 5;
	m2 = m1;

	EXPECT_EQ(3, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3), m2(7);
	m1[0][1] = 5;
	m2 = m1;

	EXPECT_EQ(m1, m2);
	EXPECT_EQ(5, m2[0][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(4), m2(4);
	m1[0][2] = 9;
	m1[3][1] = 4;
	m2[0][2] = 9;
	m2[3][1] = 4;

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(4);
	m[1][2] = 11;

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(4), m2(5);

	EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3);
	m1[0][0] = 2;
	m1[1][2] = 5;
	m2[0][0] = 3;
	m2[2][1] = 7;
	TDynamicMatrix<int> res = m1 + m2;

	EXPECT_EQ(5, res[0][0]);
	EXPECT_EQ(5, res[1][2]);
	EXPECT_EQ(7, res[2][1]);
	EXPECT_EQ(0, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(4);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3);
	m1[0][0] = 10;
	m1[1][2] = 5;
	m2[0][0] = 4;
	m2[2][1] = 7;
	TDynamicMatrix<int> res = m1 - m2;

	EXPECT_EQ(6, res[0][0]);
	EXPECT_EQ(5, res[1][2]);
	EXPECT_EQ(-7, res[2][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(4);

	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
	TDynamicMatrix<int> m(3);
	m[0][1] = 4;
	m[2][0] = 3;
	TDynamicMatrix<int> res = m * 2;

	EXPECT_EQ(8, res[0][1]);
	EXPECT_EQ(6, res[2][0]);
	EXPECT_EQ(0, res[0][0]);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 2;
	m[0][2] = 3;
	m[2][1] = 4;
	TDynamicVector<int> v(3);
	v[0] = 5;
	v[1] = 2;
	v[2] = 1;
	TDynamicVector<int> res = m * v;

	EXPECT_EQ(13, res[0]);
	EXPECT_EQ(0, res[1]);
	EXPECT_EQ(8, res[2]);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(4);

	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;
	m2[0][0] = 2; m2[0][1] = 0;
	m2[1][0] = 1; m2[1][1] = 2;
	TDynamicMatrix<int> res = m1 * m2;

	EXPECT_EQ(4, res[0][0]);
	EXPECT_EQ(4, res[0][1]);
	EXPECT_EQ(10, res[1][0]);
	EXPECT_EQ(8, res[1][1]);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);

	ASSERT_ANY_THROW(m1 * m2);
}
