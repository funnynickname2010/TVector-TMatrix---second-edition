#pragma once
#include <iostream>
#include <stdexcept>
#include <algorithm> // for std::copy and std::swap

static constexpr size_t MAX_VECTOR_SIZE = 100000000;

template<typename T>
class TDynamicVector
{
protected:
    size_t size;
    T* pMem;
public:
    TDynamicVector(size_t sz = 1);
    TDynamicVector(T* arr, size_t sz);
    TDynamicVector(const TDynamicVector<T>& v);
    TDynamicVector(TDynamicVector<T>&& v) noexcept;
    ~TDynamicVector();

    TDynamicVector<T>& operator=(const TDynamicVector<T>& v);
    TDynamicVector<T>& operator=(TDynamicVector<T>&& v) noexcept;

    size_t GetSize() const noexcept { return size; }

    T& operator[](size_t ind) noexcept;
    const T& operator[](size_t ind) const noexcept;
    T& at(size_t ind);
    const T& at(size_t ind) const;

    bool operator==(const TDynamicVector<T>& v) const noexcept;
    bool operator!=(const TDynamicVector<T>& v) const noexcept;

    TDynamicVector<T> operator+(T val);
    TDynamicVector<T> operator-(T val);
    TDynamicVector<T> operator*(T val);

    TDynamicVector<T> operator+(const TDynamicVector<T>& v);
    TDynamicVector<T> operator-(const TDynamicVector<T>& v);
    T operator*(const TDynamicVector<T>& v) noexcept(noexcept(T()));

    void swap(TDynamicVector<T>& lhs, TDynamicVector<T>& rhs) noexcept
    {
        std::swap(lhs.size, rhs.size);
        std::swap(lhs.pMem, rhs.pMem);
    }

    friend std::istream& operator>>(std::istream& istr, TDynamicVector<T>& v)
    {
        for (size_t i = 0; i < v.size; i++)
            istr >> v.pMem[i];

        return istr;
    }

    friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector<T>& v)
    {
        // (1
        ostr << '(';
        ostr << v.pMem[0];

        // , 2, 3, ..., n)
        for (size_t i = 1; i < v.size; i++)
            ostr << ', ' << v.pMem[i];

        // )
        ostr << ')';

        return ostr;
    }
};

#include "TVector.tpp"
