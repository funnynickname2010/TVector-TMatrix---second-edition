#include "tvector.h"
#include <gtest/gtest.h>

// -------------------- Vector tests --------------------

// -------------------- Constructor tests --------------------

/**
 * @brief Тест: можно создать вектор положительной длины.
 *
 * Проверяет, что конструктор TDynamicVector<int>(5) не выбрасывает исключений.
 */
TEST(TDynamicVector, can_create_vector_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

/**
 * @brief Тест: нельзя создать слишком большой вектор.
 *
 * Проверяет, что попытка создать вектор размера MAX_VECTOR_SIZE + 1 вызывает исключение.
 */
TEST(TDynamicVector, cant_create_too_large_vector)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

/**
 * @brief Тест: создание из nullptr должно выбрасывать.
 *
 * Проверяет, что конструктор, принимающий массив, выбрасывает при передаче nullptr.
 */
TEST(TDynamicVector, throws_when_create_vector_with_nullptr)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(nullptr, 5));
}

/**
 * @brief Тест: можно создать копию вектора через копирующий конструктор.
 *
 * Проверяет, что копирующий конструктор не выбрасывает исключений.
 */
TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(5);
    ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

/**
 * @brief Тест: копированный вектор равен исходному.
 *
 * Заполняет вектор v, создаёт v1 как копию и проверяет равенство.
 */
TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < v.GetSize(); i++)
        v[i] = i;
    TDynamicVector<int> v1(v);
    EXPECT_EQ(v, v1);
}

/**
 * @brief Тест: копия вектора имеет свою собственную память.
 *
 * Меняя элемент в копии, убеждаемся, что исходный вектор не изменился.
 */
TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < v.GetSize(); i++)
        v[i] = i;
    TDynamicVector<int> v1(v);
    v1[0] = 100;
    EXPECT_NE(v[0], v1[0]);
}


// -------------------- Assignment operator tests --------------------

/**
 * @brief Тест: присваивание вектора самому себе работает.
 *
 * Проверяет, что операция self-assignment не ломает объект и не выбрасывает.
 */
TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < v.GetSize(); i++)
        v[i] = i;
    ASSERT_NO_THROW(v = v);
    EXPECT_EQ(v, v);
}

/**
 * @brief Тест: присваивание между векторами одинакового размера работает.
 *
 * Проверяет, что v1 = v выполняется корректно и копирует значения.
 */
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

/**
 * @brief Тест: оператор присваивания изменяет размер при необходимости.
 *
 * Присваиваем вектор меньшего размера вектору большего размера и проверяем GetSize.
 */
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


// -------------------- GetSize test --------------------

/**
 * @brief Тест: метод GetSize возвращает корректный размер.
 */
TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(5);
    EXPECT_EQ(5, v.GetSize());
}


// -------------------- Indexing tests --------------------

/**
 * @brief Тест: установка и получение элементов через operator[] (неконстантный).
 */
TEST(TDynamicVector, can_set_and_get_element_for_square_brackets_index)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < v.GetSize(); i++)
        v[i] = i;
    for (size_t i = 0; i < v.GetSize(); i++)
        EXPECT_EQ(static_cast<int>(i), v[i]);
}

/**
 * @brief Тест: установка и получение элементов через at() с проверкой границ.
 */
TEST(TDynamicVector, can_set_and_get_element_for_at_method)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < v.GetSize(); i++)
        v.at(i) = i;
    for (size_t i = 0; i < v.GetSize(); i++)
        EXPECT_EQ(static_cast<int>(i), v.at(i));
}

/**
 * @brief Тест: доступ по индексу operator[] для константного вектора.
 *
 * Использует конструктор из массива, чтобы создать const объект.
 */
TEST(TDynamicVector, can_get_element_for_const_square_brackets_index)
{
    int arr[] = { 0, 1, 2, 3, 4 };
    const TDynamicVector<int> v(arr, 5);
    for (size_t i = 0; i < v.GetSize(); i++)
        EXPECT_EQ(static_cast<int>(i), v[i]);
}

/**
 * @brief Тест: доступ по индексу at() для константного вектора.
 */
TEST(TDynamicVector, can_get_element_for_const_at_method)
{
    int arr[] = { 0, 1, 2, 3, 4 };
    const TDynamicVector<int> v(arr, 5);
    for (size_t i = 0; i < v.GetSize(); i++)
        EXPECT_EQ(static_cast<int>(i), v.at(i));
}

/**
 * @brief Тест: at() с выходом за диапазон должен бросать.
 */
TEST(TDynamicVector, throws_when_set_element_with_too_large_index_for_at_method)
{
    TDynamicVector<int> v(5);
    ASSERT_ANY_THROW(v.at(5) = 10);
}


// -------------------- Comparison operator tests --------------------

/**
 * @brief Тест: сравнение равных векторов возвращает true.
 */
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

/**
 * @brief Тест: вектор равен сам себе.
 */
TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < v.GetSize(); i++)
        v[i] = i;
    EXPECT_TRUE(v == v);
}

/**
 * @brief Тест: векторы разных размеров не равны.
 */
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

/**
 * @brief Тест: разные векторы не равны.
 */
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

/**
 * @brief Тест: оператор != корректно определяет неравенство.
 */
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

/**
 * @brief Тест: оператор != для самого себя возвращает false.
 */
TEST(TDynamicVector, compare_vector_with_itself_return_false)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < v.GetSize(); i++)
        v[i] = i;
    EXPECT_FALSE(v != v);
}

/**
 * @brief Тест: != для векторов разного размера возвращает true.
 */
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


// -------------------- Arithmetic operation with an arithmetic value tests --------------------

/**
 * @brief Тест: добавление скаляра к каждому элементу вектора.
 */
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

/**
 * @brief Тест: вычитание скаляра из каждого элемента.
 */
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

/**
 * @brief Тест: умножение каждого элемента на скаляр.
 */
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


// -------------------- Arithmetic operation with a vector tests --------------------

/**
 * @brief Тест: поэлементное сложение векторов одинакового размера.
 */
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

/**
 * @brief Тест: сложение векторов разного размера должно бросать.
 */
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

/**
 * @brief Тест: поэлементное вычитание векторов одинакового размера.
 */
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

/**
 * @brief Тест: вычитание векторов разного размера должно бросать.
 */
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

/**
 * @brief Тест: скалярное произведение (dot) двух векторов одинакового размера.
 */
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

/**
 * @brief Тест: умножение векторов разного размера должно бросать.
 */
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


// -------------------- Swap test --------------------

/**
 * @brief Тест: обмен (swap) двух векторов.
 *
 * Создаёт два вектора разного размера, делает их копии, выполняет swap и
 * проверяет, что содержимое обменялось корректно.
 */
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

// End of tests
