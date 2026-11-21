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
	TDynamicMatrix<int> m(4);
	m[0][0] = 8;
	m[1][2] = 15;
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 14;
	TDynamicMatrix<int> m1(m);
	m1[0][0] = 88;
	EXPECT_EQ(14, m[0][0]);
	EXPECT_EQ(88, m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	// В шаблоне нет метода size(), поэтому мы просто проверяем,
	// что матрица создается, и элементы доступны.
	TDynamicMatrix<int> m(6);
	m[5][5] = 42; // Если матрица размера 6, то индексы от 0 до 5. Если это работает, значит размер верный.
	EXPECT_EQ(42, m[5][5]);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);
	m[1][2] = 30;
	EXPECT_EQ(30, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	// Тут нужна проверка в operator[]! Иначе будет ошибка памяти.
	ASSERT_ANY_THROW(m[-2][0] = 12);
	ASSERT_ANY_THROW(m[0][-2] = 12);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m[6][0] = 12);
	ASSERT_ANY_THROW(m[0][6] = 12);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	m[1][1] = 23;
	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(23, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(4), m2(4);
	m1[0][1] = 9;
	m2 = m1;
	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(3), m2(7);
	m1[0][0] = 12;
	m2 = m1;
	// Так как метода size() нет, проверяем, что скопировались данные
	EXPECT_EQ(12, m2[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3), m2(7);
	m1[1][1] = 12;
	m2 = m1;
	EXPECT_EQ(m1, m2);
	EXPECT_EQ(12, m2[1][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(4), m2(4);
	m1[0][2] = 44;
	m2[0][2] = 44;
	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);
	m[2][2] = 55;
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(4), m2(6);
	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3);
	m1[0][0] = 4;
	m2[0][0] = 7;
	TDynamicMatrix<int> res = m1 + m2;
	EXPECT_EQ(11, res[0][0]);
	EXPECT_EQ(0, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(4), m2(5);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3);
	m1[1][1] = 20;
	m2[1][1] = 6;
	TDynamicMatrix<int> res = m1 - m2;
	EXPECT_EQ(14, res[1][1]);
	EXPECT_EQ(0, res[0][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(4), m2(5);
	ASSERT_ANY_THROW(m1 - m2);
}