// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#include <iostream>
#include "TVector.h"

static constexpr size_t MAX_MATRIX_SIZE = 10000;

// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::size;
public:

	// конструктор по умолчанию
	TDynamicMatrix(size_t s = 1);

	// индексация без контроля
	using TDynamicVector<TDynamicVector<T>>::operator[];

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept;
	bool operator!=(const TDynamicMatrix& m) const noexcept;

	// матрично-скалярные операции
	TDynamicMatrix operator*(const T& val);

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v);

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m);
	TDynamicMatrix operator-(const TDynamicMatrix& m);
	TDynamicMatrix operator*(const TDynamicMatrix& m);

	// ввод/вывод
	friend std::istream& operator>>(std::istream& istr, TDynamicMatrix<T>& v)
	{
		for (size_t i = 0; i < v.size; i++)
		{
			istr >> v.pMem[i];
			std::cout << std::endl;
		}
		return istr;
	}

	friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix<T>& v)
	{
		for (size_t i = 0; i < v.size; i++)
		{
			ostr << v.pMem[i] << std::endl;
		}
		return ostr;
	}
};

#include "TMatrix.tpp"