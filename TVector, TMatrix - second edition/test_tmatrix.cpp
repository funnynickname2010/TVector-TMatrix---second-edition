#include "tmatrix.h"
#include <gtest/gtest.h>

// -------------------- Matrix tests --------------------

// -------------------- Constructor tests --------------------

/**
 * @brief Тест: можно создать матрицу положительной размерности.
 *
 * Проверяет, что конструктор TDynamicMatrix<int>(5) не выбрасывает исключений.
 */
TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

/**
 * @brief Тест: нельзя создать слишком большую матрицу.
 *
 * Проверяет, что при попытке создать матрицу размера MAX_MATRIX_SIZE + 1
 * будет выброшено исключение.
 */
TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

/**
 * @brief Тест: можно создать копию матрицы через копирующий конструктор.
 *
 * Проверяет, что копирующий конструктор не выбрасывает исключение.
 */
TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);
    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

/**
 * @brief Тест: копированная матрица равна исходной.
 *
 * Инициализирует матрицу m, создаёт m1 как копию и проверяет равенство.
 */
TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(5);
    for (size_t i = 0; i < m.GetSize(); i++)
        for (size_t j = 0; j < m.GetSize(); j++)
            m[i][j] = i * m.GetSize() + j;
    TDynamicMatrix<int> m1(m);
    EXPECT_EQ(m, m1);
}

/**
 * @brief Тест: копированная матрица имеет собственную память.
 *
 * Убеждаемся, что изменение элемента в копии не влияет на исходную матрицу.
 */
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


// -------------------- Assignment operator tests --------------------

/**
 * @brief Тест: можно присвоить матрицу самой себе.
 *
 * Проверяет, что операция присваивания саму себе работает корректно и не ломает объект.
 */
TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(5);
    for (size_t i = 0; i < m.GetSize(); i++)
        for (size_t j = 0; j < m.GetSize(); j++)
            m[i][j] = i * m.GetSize() + j;
    ASSERT_NO_THROW(m = m);
    EXPECT_EQ(m, m);
}

/**
 * @brief Тест: можно присвоить матрицу той же размерности.
 *
 * Проверяет корректность присваивания между матрицами одинакового размера.
 */
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

/**
 * @brief Тест: оператор присваивания изменяет размер матрицы при необходимости.
 *
 * Присваиваем матрицу большего размера и проверяем, что размер изменился.
 */
TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(10);
    m = m1;
    EXPECT_EQ(m.GetSize(), 10);
}


// -------------------- Comparison operator tests --------------------

/**
 * @brief Тест: сравнение равных матриц возвращает true.
 *
 * Заполняем две матрицы одинаковыми значениями и проверяем операцию ==.
 */
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

/**
 * @brief Тест: матрица равна самой себе.
 *
 * Проверяем, что сравнение матрицы с самой собой возвращает true.
 */
TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(5);
    for (size_t i = 0; i < m.GetSize(); i++)
        for (size_t j = 0; j < m.GetSize(); j++)
            m[i][j] = i * m.GetSize() + j;
    EXPECT_TRUE(m == m);
}

/**
 * @brief Тест: неравные матрицы корректно выявляются.
 *
 * Создаём две различные матрицы и проверяем оператор !=.
 */
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

/**
 * @brief Тест: матрицы разного размера считаются неравными.
 *
 * Проверяет, что матрицы с разной размерностью не равны.
 */
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


// -------------------- Arithmetic operation with a scalar tests --------------------

/**
 * @brief Тест: умножение матрицы на скаляр.
 *
 * Создаём матрицу, умножаем на скаляр и сравниваем с ожидаемым результатом.
 */
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


// -------------------- Matrix-vector multiplication tests --------------------

/**
 * @brief Тест: умножение матрицы на вектор.
 *
 * Проверяет стандартное произведение матрицы на вектор (result = m * v).
 */
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

/**
 * @brief Тест: умножение матрицы на вектор с разными размерами должно бросать.
 *
 * Проверяем, что попытка умножения матрицы и вектора несовместимых размеров
 * приводит к исключению.
 */
TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_not_equal_size)
{
    TDynamicMatrix<int> m(5);
    TDynamicVector<int> v(10);
    ASSERT_ANY_THROW(m * v);
}


// -------------------- Arithmetic operation with a matrix tests --------------------

/**
 * @brief Тест: сложение матриц одинакового размера.
 *
 * Проверяет поэлементное сложение двух матриц и сравнивает с ожидаемым результатом.
 */
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

/**
 * @brief Тест: сложение матриц разных размеров должно бросать.
 *
 * Проверяет, что попытка сложения несовместимых матриц приводит к исключению.
 */
TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(10);
    ASSERT_ANY_THROW(m + m1);
}

/**
 * @brief Тест: вычитание матриц одинакового размера.
 *
 * Проверяет поэлементное вычитание и сравнивает с ожидаемым результатом.
 */
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

/**
 * @brief Тест: вычитание матриц разных размеров должно бросать.
 *
 * Проверяет, что попытка вычитания несовместимых матриц приводит к исключению.
 */
TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(10);
    ASSERT_ANY_THROW(m - m1);
}

/**
 * @brief Тест: умножение матриц одинакового размера.
 *
 * Создаёт две конкретные 2×2 матрицы, выполняет умножение и сравнивает с заранее
 * посчитанным результатом.
 */
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

/**
 * @brief Тест: умножение матриц разного размера должно бросать.
 *
 * Проверяет, что попытка умножения несовместимых матриц приводит к исключению.
 */
TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(10);
    ASSERT_ANY_THROW(m * m1);
}


// -------------------- Swap test --------------------

/**
 * @brief Тест: обмен (swap) двух матриц.
 *
 * Создаёт две матрицы разного размера, делает их копии, выполняет swap и проверяет,
 * что содержимое обменялось корректно.
 */
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
