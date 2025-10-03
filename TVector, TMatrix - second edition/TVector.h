#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm> // for std::copy and std::swap

using namespace std;

#ifndef MAX_VECTOR_SIZE;
#define const int MAX_VECTOR_SIZE 100000000;
#endif // !MAX_VECTOR_SIZE

// ������������ ������ - 
// ��������� ������ �� ������������ ������
template<typename T>
class TDynamicVector
{
protected:
    size_t size;
    T* pMem;
public:
    // ����������� �� ���������
    TDynamicVector(size_t sz = 1);

    // ����������� �� �������
    TDynamicVector(T* arr, size_t sz);

    // ����������� �����������
    TDynamicVector(const TDynamicVector<T>& v);

    // ����������� �����������
    TDynamicVector(TDynamicVector<T>&& v) noexcept;

    // ����������
    ~TDynamicVector();

    //---------------------------------------------------------

    // ������������
    TDynamicVector<T>& operator=(const TDynamicVector<T>& v);

    // ������������ ������������
    TDynamicVector<T>& operator=(TDynamicVector<T>&& v) noexcept;

    size_t GetSize() const noexcept { return size; }

    // ����������
    T& operator[](size_t ind) noexcept;

    // ���������� ������������ �������
    const T& operator[](size_t ind) const noexcept;

    // ���������� � ���������
    T& at(size_t ind);

    // ���������� ������������ ������� � ���������
    const T& at(size_t ind) const;

    // ���������
    bool operator==(const TDynamicVector<T>& v) const noexcept;
    bool operator!=(const TDynamicVector<T>& v) const noexcept;

    // ��������� ��������
    TDynamicVector<T> operator+(T val);
    TDynamicVector<T> operator-(T val);
    TDynamicVector<T> operator*(T val);

    // ��������� ��������
    TDynamicVector<T> operator+(const TDynamicVector<T>& v);
    TDynamicVector<T> operator-(const TDynamicVector<T>& v);
    T operator*(const TDynamicVector<T>& v) noexcept(noexcept(T())); // What if T() doesn't exist?

    // �����
    friend void swap(TDynamicVector<T>& lhs, TDynamicVector<T>& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ����/�����
    friend istream& operator>>(istream& istr, TDynamicVector<T>& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // ��������� ��������>> ��� ���� T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector<T>& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // ��������� ��������<< ��� ���� T
        return ostr;
    }
};