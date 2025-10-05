#include "tvector.h"
#include <gtest/gtest.h>

// Vector tests

// Constructor tests ------------------------------------------------------------

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_nullptr)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(nullptr, 5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(5);
	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(v);
	v1[0] = 100;
	EXPECT_NE(v[0], v1[0]);
}

// Assignment operator tests ---------------------------------------------------------------

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(v, v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i + 10;
	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i + 10;
	v1 = v;
	EXPECT_EQ(v1.GetSize(), v.GetSize());
}

// GetSize() test ---------------------------------------------------------------

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(5);
	EXPECT_EQ(5, v.GetSize());
}

// Indexing tests ---------------------------------------------------------------

TEST(TDynamicVector, can_set_and_get_element_for_square_brackets_index)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	for (size_t i = 0; i < v.GetSize(); i++)
		EXPECT_EQ(static_cast<int>(i), v[i]);
}

TEST(TDynamicVector, can_set_and_get_element_for_at_method)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v.at(i) = i;
	for (size_t i = 0; i < v.GetSize(); i++)
		EXPECT_EQ(static_cast<int>(i), v.at(i));
}

TEST(TDynamicVector, can_get_element_for_const_square_brackets_index)
{
	int arr[] = {0, 1, 2, 3, 4};
	const TDynamicVector<int> v(arr, 5);
	for (size_t i = 0; i < v.GetSize(); i++)
		EXPECT_EQ(static_cast<int>(i), v[i]);
}

TEST(TDynamicVector, can_get_element_for_const_at_method)
{
	int arr[] = {0, 1, 2, 3, 4};
	const TDynamicVector<int> v(arr, 5);
	for (size_t i = 0; i < v.GetSize(); i++)
		EXPECT_EQ(static_cast<int>(i), v.at(i));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index_for_at_method)
{
	TDynamicVector<int> v(5);
	ASSERT_ANY_THROW(v.at(5) = 10);
}

// Comparison operator tests ---------------------------------------------------------------

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	EXPECT_TRUE(v == v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, compare_vectors_with_different_size_return_false)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	EXPECT_FALSE(v == v1);
}

TEST(TDynamicVector, compare_different_vectors_return_false)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i + 10;
	EXPECT_FALSE(v == v1);
}

TEST(TDynamicVector, compare_not_equal_vectors_return_true)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i + 10;
	EXPECT_TRUE(v != v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_false)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	EXPECT_FALSE(v != v);
}

TEST(TDynamicVector, compare_vectors_with_different_size_return_true)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	EXPECT_TRUE(v != v1);
}

// Arithmetic operation with an arithmetic value tests ---------------------------------------------------------------

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
		expected[i] = i + 5;
	EXPECT_EQ(expected, v + 5);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i + 5;
	TDynamicVector<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
		expected[i] = i;
	EXPECT_EQ(expected, v - 5);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i + 1;
	TDynamicVector<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
		expected[i] = (i + 1) * 5;
	EXPECT_EQ(expected, v * 5);
}

// Arithmetic operation with a vector tests ---------------------------------------------------------------

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i + 10;
	TDynamicVector<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
		expected[i] = i + (i + 10);
	EXPECT_EQ(expected, v + v1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i;
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i + 10;
	ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i + 10;
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	TDynamicVector<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
		expected[i] = (i + 10) - i;
	EXPECT_EQ(expected, v - v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i + 10;
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = i;
	ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i + 1;
	TDynamicVector<int> v1(5);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = (i + 1) * 10;
	int expected = 0;
	for (size_t i = 0; i < v.GetSize(); i++)
		expected += (i + 1) * ((i + 1) * 10);
	EXPECT_EQ(expected, v * v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i + 1;
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = (i + 1) * 10;
	ASSERT_ANY_THROW(v * v1);
}

// Swap test ---------------------------------------------------------------

TEST(TDynamicVector, can_swap_vectors)
{
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i + 1;
	TDynamicVector<int> v1(10);
	for (size_t i = 0; i < v1.GetSize(); i++)
		v1[i] = (i + 1) * 10;
	TDynamicVector<int> v_copy = v;
	TDynamicVector<int> v1_copy = v1;
	v.swap(v, v1);
	EXPECT_EQ(v, v1_copy);
	EXPECT_EQ(v1, v_copy);
}

// End of tests ---------------------------------------------------------------