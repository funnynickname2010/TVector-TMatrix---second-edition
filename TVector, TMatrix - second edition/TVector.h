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
    TDynamicVector(const TDynamicVector& v);

    // ����������� �����������
    TDynamicVector(TDynamicVector&& v) noexcept;

    // ����������
    ~TDynamicVector();

    //---------------------------------------------------------

    // ������������
    TDynamicVector& operator=(const TDynamicVector& v);

    // ������������ ������������
    TDynamicVector& operator=(TDynamicVector&& v) noexcept;

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
    bool operator==(const TDynamicVector& v) const noexcept;
    bool operator!=(const TDynamicVector& v) const noexcept;

    // ��������� ��������
    TDynamicVector operator+(T val);
    TDynamicVector operator-(T val);
    TDynamicVector operator*(T val);

    // ��������� ��������
    TDynamicVector operator+(const TDynamicVector& v);
    TDynamicVector operator-(const TDynamicVector& v);
    T operator*(const TDynamicVector& v) noexcept(noexcept(T())); // What if T() doesn't exist?

    // �����
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ����/�����
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // ��������� ��������>> ��� ���� T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // ��������� ��������<< ��� ���� T
        return ostr;
    }
};