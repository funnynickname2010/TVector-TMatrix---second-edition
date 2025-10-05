// Constructor --------------------------------------------------------

/**
 * @brief Конструктор квадратной матрицы размера s.
 *
 * Создаёт матрицу размера s × s, вызывая конструктор базового вектора
 * TDynamicVector<TDynamicVector<T>> для выделения памяти под строки,
 * затем инициализирует каждую строку как TDynamicVector<T>(size).
 *
 * @tparam T Тип элементов матрицы.
 * @param s Размер (количество строк и столбцов) матрицы.
 * @throws std::out_of_range если s == 0.
 * @throws std::length_error если s > MAX_MATRIX_SIZE.
 */
template <class T>
TDynamicMatrix<T>::TDynamicMatrix(size_t s) : TDynamicVector<TDynamicVector<T>>(s)
{
	if (s == 0)
	{
		throw std::out_of_range("Matrix size should be greater than zero");
	}

	if (s > MAX_MATRIX_SIZE)
	{
		throw std::length_error("Matrix size exceeds maximum allowed size");
	}

	for (size_t i = 0; i < size; i++)
	{
		pMem[i] = TDynamicVector<T>(size);
	}
}

// Equality/inequality operators -----------------------------------------------------------------

/**
 * @brief Оператор сравнения на равенство.
 *
 * Сравнивает текущую матрицу с матрицей m по размеру и по содержимому каждой строки.
 *
 * @tparam T Тип элементов матрицы.
 * @param m Матрица, с которой производится сравнение.
 * @return true если размеры совпадают и все соответствующие строки равны, иначе false.
 */
template <class T>
bool TDynamicMatrix<T>::operator==(const TDynamicMatrix<T>& m) const noexcept
{
	bool result = true;
	if (size != m.size)
	{
		result = false;
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			if (pMem[i] != m.pMem[i])
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

/**
 * @brief Оператор неравенства.
 *
 * Инвертирует результат оператора ==.
 *
 * @tparam T Тип элементов матрицы.
 * @param m Матрица для сравнения.
 * @return true если матрицы различаются, иначе false.
 */
template <class T>
bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix<T>& m) const noexcept
{
	return !(*this == m);
}

// Matrix-scalar multiplication -----------------------------------------------------------------

/**
 * @brief Умножение матрицы на скаляр.
 *
 * Возвращает новую матрицу, каждый элемент которой равен соответствующему
 * элементу исходной матрицы, умноженному на val.
 *
 * @tparam T Тип элементов матрицы.
 * @param val Скаляр для умножения.
 * @return Новая матрица такого же размера, результат умножения.
 */
template <class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const T& val)
{
	TDynamicMatrix<T> result(size);
	for (size_t i = 0; i < size; i++)
	{
		result.pMem[i] = pMem[i] * val;
	}
	return result;
}

// Matrix-vector multiplication -----------------------------------------------------------------

/**
 * @brief Умножение матрицы на вектор (матрица * вектор).
 *
 * Выполняет стандартное умножение: результат[i] = dot(pMem[i], v).
 *
 * @tparam T Тип элементов матрицы/вектора.
 * @param v Входной вектор; его размер должен совпадать с размером матрицы.
 * @throws std::invalid_argument если размер вектора не совпадает с размером матрицы.
 * @return Вектор-результат умножения размером size.
 */
template <class T>
TDynamicVector<T> TDynamicMatrix<T>::operator*(const TDynamicVector<T>& v)
{
	if (size != v.GetSize())
	{
		throw std::invalid_argument("Matrix columns must match vector size for multiplication");
	}
	TDynamicVector<T> result(size);
	for (size_t i = 0; i < size; i++)
	{
		result[i] = pMem[i] * v;
	}
	return result;
}

// Matrix-matrix operations -----------------------------------------------------------------

/**
 * @brief Сложение двух матриц.
 *
 * Проверяет совместимость размеров (матрицы должны быть одинакового размера
 * и соответствующие строки должны иметь одинаковую длину) и возвращает
 * новую матрицу, в которой каждая строка — сумма соответствующих строк.
 *
 * @tparam T Тип элементов матрицы.
 * @param m Правая матрица для сложения.
 * @throws std::invalid_argument если размеры несовместимы.
 * @return Новая матрица — результат сложения.
 */
template <class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator+(const TDynamicMatrix<T>& m)
{
	bool size_equal = true;

	if (size != m.size)
	{
		size_equal = false;
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			if (pMem[i].GetSize() != m.pMem[i].GetSize())
			{
				size_equal = false;
				break;
			}
		}
	}

	if (!size_equal)
	{
		throw std::invalid_argument("Matrices must be of the same size for addition");
	}

	TDynamicMatrix<T> result(size);

	for (size_t i = 0; i < size; i++)
	{
		result.pMem[i] = pMem[i] + m.pMem[i];
	}
	return result;
}

/**
 * @brief Вычитание двух матриц.
 *
 * Проверяет совместимость размеров и возвращает новую матрицу,
 * представляющую разность соответствующих строк.
 *
 * @tparam T Тип элементов матрицы.
 * @param m Правая матрица для вычитания.
 * @throws std::invalid_argument если размеры несовместимы.
 * @return Новая матрица — результат вычитания.
 */
template <class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator-(const TDynamicMatrix<T>& m)
{
	bool size_equal = true;
	if (size != m.size)
	{
		size_equal = false;
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			if (pMem[i].GetSize() != m.pMem[i].GetSize())
			{
				size_equal = false;
				break;
			}
		}
	}
	if (!size_equal)
	{
		throw std::invalid_argument("Matrices must be of the same size for subtraction");
	}
	TDynamicMatrix<T> result(size);
	for (size_t i = 0; i < size; i++)
	{
		result.pMem[i] = pMem[i] - m.pMem[i];
	}
	return result;
}

/**
 * @brief Умножение двух матриц (матричные произведения).
 *
 * Выполняет классическое матричное умножение: result = (*this) * m.
 * Перед выполнением проверяет совместимость размеров (в данном коде —
 * квадраты одинакового размера).
 *
 * @tparam T Тип элементов матрицы.
 * @param m Правая матрица для умножения.
 * @throws std::invalid_argument если размеры несовместимы.
 * @return Новая матрица — результат умножения.
 */
template <class T>
TDynamicMatrix<T> TDynamicMatrix<T>::operator*(const TDynamicMatrix<T>& m)
{
	bool size_fine = true;
	if (size != m.size)
	{
		size_fine = false;
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			if (pMem[i].GetSize() != m.pMem[i].GetSize())
			{
				size_fine = false;
				break;
			}
		}
	}

	if (!size_fine)
	{
		throw std::invalid_argument("Matrices must be of the same size (not mathematically though) for multiplication");
	}

	TDynamicMatrix<T> result(size);

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			result.pMem[i][j] = T();
			for (size_t k = 0; k < size; k++)
			{
				result.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
			}
		}
	}
	return result;
}

// swap -----------------------------------------------------------------

/**
 * @brief Обмен (swap) содержимого двух матриц.
 *
 * Обменивает значения полей size и указателей pMem между lhs и rhs.
 * Помечен noexcept — не выбрасывает исключений.
 *
 * @tparam T Тип элементов матрицы.
 * @param lhs Левая матрица.
 * @param rhs Правая матрица.
 */
template <class T>
void TDynamicMatrix<T>::swap(TDynamicMatrix& lhs, TDynamicMatrix& rhs) noexcept
{
	std::swap(lhs.size, rhs.size);
	std::swap(lhs.pMem, rhs.pMem);
}
