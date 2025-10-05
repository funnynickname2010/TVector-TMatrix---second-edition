// -------------------- Constructors and destructor --------------------

/**
 * @brief Конструктор вектора заданного размера.
 *
 * Выделяет память под sz элементов типа T и инициализирует её значениями по умолчанию.
 *
 * @tparam T Тип элементов вектора.
 * @param sz Желаемый размер вектора (должен быть > 0 и <= MAX_VECTOR_SIZE).
 * @throws std::out_of_range если sz == 0.
 * @throws std::length_error если sz > MAX_VECTOR_SIZE.
 */
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

/**
 * @brief Конструктор из массива.
 *
 * Копирует sz элементов из массива arr в новый вектор.
 *
 * @tparam T Тип элементов.
 * @param arr Указатель на входной массив (не должен быть nullptr).
 * @param sz Количество элементов для копирования (>0 и <= MAX_VECTOR_SIZE).
 * @throws std::invalid_argument если arr == nullptr.
 * @throws std::out_of_range если sz == 0.
 * @throws std::length_error если sz > MAX_VECTOR_SIZE.
 */
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

/**
 * @brief Копирующий конструктор.
 *
 * Выполняет глубокое копирование массива данных из v.
 *
 * @tparam T Тип элементов.
 * @param v Вектор-источник для копирования.
 */
template <class T>
TDynamicVector<T>::TDynamicVector(const TDynamicVector<T>& v) : size(v.size)
{
    pMem = new T[size];
    std::copy(v.pMem, v.pMem + size, pMem);
}

/**
 * @brief Перемещающий конструктор.
 *
 * Захватывает ресурсы у v и оставляет v в валидном пустом состоянии.
 *
 * @tparam T Тип элементов.
 * @param v Rvalue-ссылка на вектор-источник.
 * @note noexcept гарантируется.
 */
template <class T>
TDynamicVector<T>::TDynamicVector(TDynamicVector<T>&& v) noexcept : size(v.size), pMem(v.pMem)
{
    std::swap(v.size, size);
    std::swap(v.pMem, pMem);
    size = 0;
    pMem = nullptr;
}

/**
 * @brief Деструктор.
 *
 * Освобождает выделенную под элементы память, если она существует.
 *
 * @tparam T Тип элементов.
 */
template <class T>
TDynamicVector<T>::~TDynamicVector()
{
    if (pMem != nullptr)
    {
        delete[] pMem;
        pMem = nullptr;
    }
}


// -------------------- Assignment operators --------------------

/**
 * @brief Оператор копирующего присваивания.
 *
 * Реализует присваивание с обработкой изменения размера: при необходимости
 * выделяет новую память, копирует данные и освобождает старую память.
 *
 * @tparam T Тип элементов.
 * @param v Правый операнд присваивания.
 * @return Ссылка на *this.
 */
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

/**
 * @brief Оператор перемещающего присваивания.
 *
 * Освобождает текущие ресурсы и принимает ресурсы от v. После операции v
 * остаётся в пустом/валидном состоянии.
 *
 * @tparam T Тип элементов.
 * @param v Rvalue-ссылка на вектор-источник.
 * @return Ссылка на *this.
 * @note noexcept гарантируется.
 */
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


// -------------------- Element access --------------------

/**
 * @brief Неконстантный оператор доступа по индексу.
 *
 * Быстрый доступ без проверки границ.
 *
 * @tparam T Тип элементов.
 * @param ind Индекс элемента.
 * @return Ссылка на элемент (lvalue).
 */
template <class T>
T& TDynamicVector<T>::operator[](size_t ind) noexcept
{
    return pMem[ind];
}

/**
 * @brief Константный оператор доступа по индексу.
 *
 * Быстрый доступ без проверки границ для константного вектора.
 *
 * @tparam T Тип элементов.
 * @param ind Индекс элемента.
 * @return Константная ссылка на элемент.
 */
template <class T>
const T& TDynamicVector<T>::operator[](size_t ind) const noexcept
{
    return pMem[ind];
}

/**
 * @brief Метод at() с проверкой границ (неконстантный).
 *
 * @tparam T Тип элементов.
 * @param ind Индекс элемента.
 * @return Ссылка на элемент.
 * @throws std::out_of_range если ind >= size.
 */
template <class T>
T& TDynamicVector<T>::at(size_t ind)
{
    if (ind >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return pMem[ind];
}

/**
 * @brief Метод at() с проверкой границ (константный).
 *
 * @tparam T Тип элементов.
 * @param ind Индекс элемента.
 * @return Константная ссылка на элемент.
 * @throws std::out_of_range если ind >= size.
 */
template <class T>
const T& TDynamicVector<T>::at(size_t ind) const
{
    if (ind >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return pMem[ind];
}


// -------------------- Comparison operators --------------------

/**
 * @brief Оператор сравнения на равенство.
 *
 * Сравнивает размеры и попарно элементы векторов.
 *
 * @tparam T Тип элементов.
 * @param v Вектор для сравнения.
 * @return true если размеры и все элементы равны, иначе false.
 */
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

/**
 * @brief Оператор неравенства.
 *
 * Инвертирует результат оператора ==.
 *
 * @tparam T Тип элементов.
 * @param v Вектор для сравнения.
 * @return true если векторы не равны, иначе false.
 */
template <class T>
bool TDynamicVector<T>::operator!=(const TDynamicVector<T>& v) const noexcept
{
    return !(*this == v);
}


// -------------------- Scalar operations --------------------

/**
 * @brief Побитовое/арифметическое (элементное) прибавление скаляра.
 *
 * Возвращает новый вектор, в котором к каждому элементу добавлен val.
 *
 * @tparam T Тип элементов.
 * @param val Скаляр для прибавления.
 * @return Новый вектор размера size с обновлёнными элементами.
 */
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

/**
 * @brief Элементное вычитание скаляра.
 *
 * Возвращает новый вектор, из каждого элемента которого вычтен val.
 *
 * @tparam T Тип элементов.
 * @param val Скаляр для вычитания.
 * @return Новый вектор размера size.
 */
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

/**
 * @brief Элементное умножение на скаляр.
 *
 * Возвращает новый вектор, где каждый элемент умножен на val.
 *
 * @tparam T Тип элементов.
 * @param val Скаляр для умножения.
 * @return Новый вектор размера size.
 */
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


// -------------------- Vector operations --------------------

/**
 * @brief Сложение двух векторов.
 *
 * Выполняет поэлементное сложение; размеры векторов должны совпадать.
 *
 * @tparam T Тип элементов.
 * @param v Правый вектор для сложения.
 * @throws std::invalid_argument если размеры не совпадают.
 * @return Новый вектор — результат сложения.
 */
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

/**
 * @brief Вычитание двух векторов.
 *
 * Выполняет поэлементное вычитание; размеры векторов должны совпадать.
 *
 * @tparam T Тип элементов.
 * @param v Правый вектор для вычитания.
 * @throws std::invalid_argument если размеры не совпадают.
 * @return Новый вектор — результат вычитания.
 */
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


// -------------------- Dot product --------------------

/**
 * @brief Скалярное (dot) произведение двух векторов.
 *
 * Вычисляет суммарное произведение соответствующих элементов.
 *
 * @tparam T Тип элементов (должен поддерживать операцию умножения и сложения).
 * @param v Вектор-правый операнд.
 * @throws std::invalid_argument если размеры векторов не совпадают.
 * @return Скаляр типа T — результат скалярного произведения.
 * @note noexcept спецификация зависит от noexcept(T()) — если конструктор T() noexcept,
 *       то функция помечается noexcept.
 */
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
