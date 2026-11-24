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
	m[0][2] = 123;
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(m,m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	m[0][1] = 5;
	m[1][2] = 123;
	TDynamicMatrix<int> m1(m);
	m1[2][4] = 10;
	EXPECT_NE			(m, m1);
	//ADD_FAILURE();
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(4);
	EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);
	m[0][2] = 4;
	EXPECT_EQ(4, m[0][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(-1) = 10);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(13128012435468) = 10);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(12);
	m[2][3] = 52;
	m[5][5] = 67;
	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(52, m[2][3]);
	EXPECT_EQ(67, m[5][5]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(12);
	TDynamicMatrix<int> m1(12);
	m[3][1] = 52;
	m[5][2] = 67;
	m1[0] = 42;
	ASSERT_NO_THROW(m = m1);
	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(12);
	m = m1;
	EXPECT_EQ(12, m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(12);
	m[3][1] = 52;
	m[4][2] = 67;
	m1[0] = 42;
	m = m1;
	EXPECT_EQ(m1, m);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	m[0][1] = 4;
	m1[0][1] = 4;
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);
	m[0][1] = 4;
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(10);
	EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> v(3);
	TDynamicMatrix<int> res(3);
	TDynamicMatrix<int> v2(3);
	TDynamicMatrix<int> tru(3);
	tru[0][1] = 20;
	tru[1][2] = 25;
	tru[2][1] = 30;
	v2[0][1] = 16;
	v2[1][2] = 20;
	v2[2][1] = 24;
	v[0][1] = 4;
	v[1][2] = 5;
	v[2][1] = 6;
	res = v + v2;
	EXPECT_EQ(res, tru);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(17);
	m[2][2] = 123;
	ASSERT_ANY_THROW(m1 + m);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> v(3);
	TDynamicMatrix<int> res(3);
	TDynamicMatrix<int> v2(3);
	TDynamicMatrix<int> tru(3);
	tru[0][1] = 12;
	tru[1][2] = 15;
	tru[2][1] = 18;
	v2[0][1] = 16;
	v2[1][2] = 20;
	v2[2][1] = 24;
	v[0][1] = 4;
	v[1][2] = 5;
	v[2][1] = 6;
	res = v2 - v;
	EXPECT_EQ(res, tru);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(17);
	m[2][2] = 123;
	ASSERT_ANY_THROW(m1 - m);
}

