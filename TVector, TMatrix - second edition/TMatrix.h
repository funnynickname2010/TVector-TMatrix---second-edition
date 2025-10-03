// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include "TVector.h"

using namespace std;

#ifndef MAX_MATRIX_SIZE
#define const int MAX_MATRIX_SIZE 10000;
#endif // !MAX_MATRIX_SIZE

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
	friend istream& operator>>(istream& istr, TDynamicMatrix& v);
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v);
};
#endif