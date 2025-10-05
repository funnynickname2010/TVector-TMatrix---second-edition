#include "tmatrix.h"
#include <gtest/gtest.h>

// Matrix tests

// Constructor tests ------------------------------------------------------------

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> m1(m);
	m1[0][0] = 100;
	EXPECT_NE(m[0][0], m1[0][0]);
}

// Assignment operator tests ---------------------------------------------------------------

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> m1(5);
	for (size_t i = 0; i < m1.GetSize(); i++)
		for (size_t j = 0; j < m1.GetSize(); j++)
			m1[i][j] = (i + 1) * m1.GetSize() + (j + 1);
	ASSERT_NO_THROW(m = m1);
	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(10);
	m = m1;
	EXPECT_EQ(m.GetSize(), 10);
}

// Comparison operator tests ---------------------------------------------------------------

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> m1(5);
	for (size_t i = 0; i < m1.GetSize(); i++)
		for (size_t j = 0; j < m1.GetSize(); j++)
			m1[i][j] = i * m1.GetSize() + j;
	EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, compare_not_equal_matrices_return_true)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> m1(5);
	for (size_t i = 0; i < m1.GetSize(); i++)
		for (size_t j = 0; j < m1.GetSize(); j++)
			m1[i][j] = (i + 1) * m1.GetSize() + (j + 1);
	EXPECT_TRUE(m != m1);
}

TEST(TDynamicMatrix, compare_matrices_with_different_size_return_true)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> m1(10);
	for (size_t i = 0; i < m1.GetSize(); i++)
		for (size_t j = 0; j < m1.GetSize(); j++)
			m1[i][j] = i * m1.GetSize() + j;
	EXPECT_TRUE(m != m1);
}

// Arithmetic operation with a scalar tests ---------------------------------------------------------------

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
		for (size_t j = 0; j < expected.GetSize(); j++)
			expected[i][j] = (i * expected.GetSize() + j) * 5;
	EXPECT_EQ(expected, m * 5);
}

// Matrix-vector multiplication tests ---------------------------------------------------------------

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicVector<int> v(5);
	for (size_t i = 0; i < v.GetSize(); i++)
		v[i] = i + 1;
	TDynamicVector<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
	{
		expected[i] = 0;
		for (size_t j = 0; j < v.GetSize(); j++)
			expected[i] += m[i][j] * v[j];
	}
	EXPECT_EQ(expected, m * v);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicVector<int> v(10);
	ASSERT_ANY_THROW(m * v);
}

// Arithmetic operation with a matrix tests ---------------------------------------------------------------

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> m1(5);
	for (size_t i = 0; i < m1.GetSize(); i++)
		for (size_t j = 0; j < m1.GetSize(); j++)
			m1[i][j] = (i + 1) * m1.GetSize() + (j + 1);
	TDynamicMatrix<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
		for (size_t j = 0; j < expected.GetSize(); j++)
			expected[i][j] = (i * expected.GetSize() + j) + ((i + 1) * expected.GetSize() + (j + 1));
	EXPECT_EQ(expected, m + m1);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(10);
	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = (i + j) * 2;
	TDynamicMatrix<int> m1(5);
	for (size_t i = 0; i < m1.GetSize(); i++)
		for (size_t j = 0; j < m1.GetSize(); j++)
			m1[i][j] = i + j;
	TDynamicMatrix<int> expected(5);
	for (size_t i = 0; i < expected.GetSize(); i++)
		for (size_t j = 0; j < expected.GetSize(); j++)
			expected[i][j] = i + j;
	EXPECT_EQ(expected, m - m1);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(10);
	ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 2;
	m[1][0] = 3; m[1][1] = 4;
	TDynamicMatrix<int> m1(2);
	m1[0][0] = 5; m1[0][1] = 6;
	m1[1][0] = 7; m1[1][1] = 8;
	TDynamicMatrix<int> expected(2);
	expected[0][0] = 19; expected[0][1] = 22;
	expected[1][0] = 43; expected[1][1] = 50;
	EXPECT_EQ(expected, m * m1);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(10);
	ASSERT_ANY_THROW(m * m1);
}

// Swap test ---------------------------------------------------------------
TEST(TDynamicMatrix, can_swap_matrices)
{
	TDynamicMatrix<int> m(5);
	for (size_t i = 0; i < m.GetSize(); i++)
		for (size_t j = 0; j < m.GetSize(); j++)
			m[i][j] = i * m.GetSize() + j;
	TDynamicMatrix<int> m1(10);
	for (size_t i = 0; i < m1.GetSize(); i++)
		for (size_t j = 0; j < m1.GetSize(); j++)
			m1[i][j] = i * m1.GetSize() + j;
	TDynamicMatrix<int> m_copy = m;
	TDynamicMatrix<int> m1_copy = m1;
	m.swap(m, m1);
	EXPECT_EQ(m, m1_copy);
	EXPECT_EQ(m1, m_copy);
}