// ����������� �� ��������� --------------------------------------------------------
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

// ��������� -----------------------------------------------------------------
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

template <class T>
bool TDynamicMatrix<T>::operator!=(const TDynamicMatrix<T>& m) const noexcept
{
	return !(*this == m);
}

// ��������-��������� �������� -----------------------------------------------------------------
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

// ��������-��������� �������� -----------------------------------------------------------------
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

// ��������-��������� �������� -----------------------------------------------------------------
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