#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(12);
	v[0] = 8;
	v[1] = 15;
	TDynamicVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10);
	v1.at(0) = 14;
	TDynamicVector<int> v2(v1);
	v2.at(0) = 88;
	EXPECT_EQ(14, v1.at(0));
	EXPECT_EQ(88, v2.at(0));
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(6);
	EXPECT_EQ(6, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(-2));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(6));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);
	v.at(0) = 23;
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(23, v.at(0));
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	v1[0] = 9;
	v2 = v1;
	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(4), v2(9);
	v1[0] = 12;
	v2 = v1;
	EXPECT_EQ(4, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(4), v2(9);
	v1[0] = 12;
	v2 = v1;
	EXPECT_EQ(v1, v2);
	EXPECT_EQ(12, v2[0]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(5), v2(5);
	v1[0] = 30;
	v1[3] = 11;
	v2[0] = 30;
	v2[3] = 11;
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(5);
	v[2] = 44;
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(6), v2(8);
	EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	v[1] = 4;
	TDynamicVector<int> res = v + 7;
	EXPECT_EQ(7, res[0]);
	EXPECT_EQ(11, res[1]);
	EXPECT_EQ(7, res[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	v[1] = 15;
	TDynamicVector<int> res = v - 6;
	EXPECT_EQ(-6, res[0]);
	EXPECT_EQ(9, res[1]);
	EXPECT_EQ(-6, res[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(4);
	v[0] = 3;
	v[3] = 7;
	TDynamicVector<int> res = v * 4;
	EXPECT_EQ(12, res[0]);
	EXPECT_EQ(0, res[1]);
	EXPECT_EQ(28, res[3]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	v1[0] = 4;
	v1[2] = 8;
	v2[0] = 7;
	v2[4] = 10;
	TDynamicVector<int> res = v1 + v2;
	EXPECT_EQ(11, res[0]);
	EXPECT_EQ(8, res[2]);
	EXPECT_EQ(10, res[4]);
	EXPECT_EQ(0, res[1]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4), v2(7);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	v1[1] = 20;
	v2[1] = 6;
	v2[3] = 8;
	TDynamicVector<int> res = v1 - v2;
	EXPECT_EQ(14, res[1]);
	EXPECT_EQ(-8, res[3]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(4), v2(7);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
	v1[0] = 3;
	v1[3] = 6;
	v2[0] = 5;
	v2[1] = 12;
	v2[3] = 2;
	EXPECT_EQ(27, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5),v2(6);
	EXPECT_EQ(0, v1 * v2);
}