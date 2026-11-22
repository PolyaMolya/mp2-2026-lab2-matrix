#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(3);
	v[0] = 10;
	v[1] = 20;
	v[2] = 30;
	TDynamicVector<int> v_copy(v);
	EXPECT_TRUE(v == v_copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory) // Проверка, что данные оригинала не поменялись, после копирования
{
	TDynamicVector<int> v(3);
	v[0] = 10;
	TDynamicVector<int> v_copy(v);
	v_copy[0] = 99;
	EXPECT_EQ(v[0], 10);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);
  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(7));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(3);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v = v;
	EXPECT_EQ(v.size(), 3);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v[2], 3);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 8; v2[1] = 7; v2[2] = 6;
	v1 = v2;
	EXPECT_EQ(v1[0], 8);
	EXPECT_EQ(v1[1], 7);
	EXPECT_EQ(v1[2], 6);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(2);
	v2[0] = 7;
	v1 = v2;
	EXPECT_EQ(v1.size(), 2);
	EXPECT_EQ(v1[0], 7);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(2);
	v2[0] = 50;
	v2[1] = 40;
	v1 = v2;
	EXPECT_EQ(v1.size(), 2);
	EXPECT_EQ(v1[0], 50);
	EXPECT_EQ(v1[1], 40);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	v1[0] = 314; v1[1] = 271; v1[2] = 141;
	v2[0] = 314; v2[1] = 271; v2[2] = 141;
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(2);
	v[0] = 888;
	v[1] = -15;
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(4);
	v1[0] = 777;
	v2[0] = 777;
	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 11; v[1] = 22; v[2] = 33;
	TDynamicVector<int> res = v + 5;
	EXPECT_EQ(res[0], 16);
	EXPECT_EQ(res[1], 27);
	EXPECT_EQ(res[2], 38);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(2);
	v[0] = 90;
	v[1] = 45;
	TDynamicVector<int> res = v - 10;
	EXPECT_EQ(res[0], 80);
	EXPECT_EQ(res[1], 35);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 2;
	v[1] = -4;
	v[2] = 7;
	TDynamicVector<int> res = v * 3;
	EXPECT_EQ(res[0], 6);
	EXPECT_EQ(res[1], -12);
	EXPECT_EQ(res[2], 21);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);
	v1[0] = 10; v1[1] = 20; v1[2] = 30;
	v2[0] = 1; v2[1] = 2; v2[2] = 3;
	TDynamicVector<int> res = v1 + v2;
	EXPECT_EQ(res[0], 11);
	EXPECT_EQ(res[1], 22);
	EXPECT_EQ(res[2], 33);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(3); 

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(2);
	v1[0] = 50; v1[1] = 100;
	v2[0] = 5; v2[1] = 20;
	TDynamicVector<int> res = v1 - v2;
	EXPECT_EQ(res[0], 45);
	EXPECT_EQ(res[1], 80);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(2);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3);
	TDynamicVector<int> v2(3);

	v1[0] = 2; v1[1] = 3; v1[2] = 4;
	v2[0] = 5; v2[1] = 6; v2[2] = 7;
	int res = v1 * v2;
	EXPECT_EQ(res, 56);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(2);
	TDynamicVector<int> v2(4);
	ASSERT_ANY_THROW(v1 * v2);
}

