// ������������ � ���������� ---------------------------------------------------------

template <class T>
TDynamicVector<T>::TDynamicVector(size_t sz) : size(sz)
{
    if (sz == 0)
    {
        throw std::out_of_range("Vector size should be greater than zero");
    }

    if (sz > MAX_VECTOR_SIZE)
    {
        throw std::length_error("Vector size exceeds maximum allowed size");
    }

    pMem = new T[sz]();
}

template <class T>
TDynamicVector<T>::TDynamicVector(T* arr, size_t sz) : size(sz)
{
    if (arr == nullptr)
    {
        throw std::invalid_argument("Input array cannot be nullptr");
    }

    if (sz == 0)
    {
        throw std::out_of_range("Vector size should be greater than zero");
    }

    if (sz > MAX_VECTOR_SIZE)
    {
        throw std::length_error("Vector size exceeds maximum allowed size");
    }

    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
}

template <class T>
TDynamicVector<T>::TDynamicVector(const TDynamicVector<T>& v) : size(v.size)
{
    pMem = new T[size];
    std::copy(v.pMem, v.pMem + size, pMem);
}

template <class T>
TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& v) noexcept : size(v.size), pMem(v.pMem)
{
	std::swap(v.size, size);
	std::swap(v.pMem, pMem);
    size = 0;
	pMem = nullptr;
}

template <class T>
TDynamicVector<T>::~TDynamicVector()
{
    if (pMem != nullptr)
    {
        delete[] pMem;
        pMem = nullptr;
    }
}

// ������������ � ����������� -----------------------------------------------------------------

template <class T>
TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector<T>& v)
{
    if (this != &v) // self-assignment check
    {
        if (size != v.size)
        {
            T* newMem = nullptr;

            newMem = new T[v.size];

            delete[] pMem; // free old memory
            pMem = newMem;
            size = v.size;
        }
        std::copy(v.pMem, v.pMem + size, pMem);
    }
    return *this;
}

// ??? Move assignment operator
template <class T>
TDynamicVector<T>& TDynamicVector<T>::operator=(TDynamicVector<T>&& v) noexcept
{
    if (this != &v) // self-assignment check
    {
        delete[] pMem; // free old memory
        // Transfer ownership of memory
        size = v.size;
        pMem = v.pMem;
        v.size = 0;
        v.pMem = nullptr;
    }
    return *this;
}

// ���������� -----------------------------------------------------------------

template <class T>
T& TDynamicVector<T>::operator[](size_t ind) noexcept
{
    return pMem[ind];
}

template <class T>
const T& TDynamicVector<T>::operator[](size_t ind) const noexcept
{
    return pMem[ind];
}

template <class T>
T& TDynamicVector<T>::at(size_t ind)
{
    if (ind >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return pMem[ind];
}

template <class T>
const T& TDynamicVector<T>::at(size_t ind) const
{
    if (ind >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return pMem[ind];
}

// c�������� -----------------------------------------------------------------

template <class T>
bool TDynamicVector<T>::operator==(const TDynamicVector<T>& v) const noexcept
{
    bool result = true;

    if (size != v.size)
    {
        result = false;
    }
    else
    {
        for (size_t i = 0; i < size; i++)
        {
            if (pMem[i] != v.pMem[i])
            {
                result = false;
                break;
            }
        }
    }
    return result;
}

template <class T>
bool TDynamicVector<T>::operator!=(const TDynamicVector<T>& v) const noexcept
{
    return !(*this == v);
}

// ��������� �������� -----------------------------------------------------------------

template <class T>
TDynamicVector<T> TDynamicVector<T>::operator+(T val)
{
    TDynamicVector<T> result(size);
    for (size_t i = 0; i < size; i++)
    {
        result.pMem[i] = pMem[i] + val;
    }
    return result;
}

template <class T>
TDynamicVector<T> TDynamicVector<T>::operator-(T val)
{
    TDynamicVector<T> result(size);
    for (size_t i = 0; i < size; i++)
    {
        result.pMem[i] = pMem[i] - val;
    }
    return result;
}

template <class T>
TDynamicVector<T> TDynamicVector<T>::operator*(T val)
{
    TDynamicVector<T> result(size);
    for (size_t i = 0; i < size; i++)
    {
        result.pMem[i] = pMem[i] * val;
    }
    return result;
}

// ��������� �������� -----------------------------------------------------------------

template <class T>
TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector<T>& v)
{
    if (size != v.size)
    {
        throw std::invalid_argument("Vectors must be of the same size for addition");
    }
    TDynamicVector<T> result(size);
    for (size_t i = 0; i < size; i++)
    {
        result.pMem[i] = pMem[i] + v.pMem[i];
    }
    return result;
}

template <class T>
TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector<T>& v)
{
    if (size != v.size)
    {
        throw std::invalid_argument("Vectors must be of the same size for subtraction");
    }
    TDynamicVector<T> result(size);
    for (size_t i = 0; i < size; i++)
    {
        result.pMem[i] = pMem[i] - v.pMem[i];
    }
    return result;
}

template <class T>
T TDynamicVector<T>::operator*(const TDynamicVector<T>& v) noexcept(noexcept(T()))
{
    if (size != v.size)
    {
        throw std::invalid_argument("Vectors must be of the same size for dot product");
    }
    T result = T();
    for (size_t i = 0; i < size; i++)
    {
        result += pMem[i] * v.pMem[i];
    }
    return result;
}