#pragma once

#include <algorithm>

template <typename T>
class Vector {
public:
    Vector();
    ~Vector() { delete [] elem_; }
    Vector<T>& operator=(Vector<T> const& other);
    unsigned size() const { return size_; }

    T& operator[](unsigned i) const { return elem_[i]; }

protected:
    void copyFrom(T const* other, unsigned lo, unsigned hi);
    void expand();
    void shrink();

    constexpr usnigned DEFAULT_CAPACITY = 8;
    T* elem_;
    unsigned capacity_;
    unsigned size_;
};

template <typename T>
Vector<T>::Vector() : capacity_(DEFAULT_CAPACITY), size_(0), elem_(new T[capacity_]){}

template <typename T>
void Vector<T>::copyFrom(T const* other, unsigned lo, unsigned hi)
{
    elem_ = new T[capacity_ = 2*(hi-lo)];
    size_ = 0;
    while (lo < hi) { elem_[size_++] = other[lo++]; }
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& other)
{
    if (elem_) { delete elem_; }
    copyFrom(other.elem_, 0, other.size());
    return *this;
}

template <typename T>
void Vector<T>::expand()
{
    if (size_ < capacity_) { return; }
    if (capacity_ < DEFAULT_CAPACITY) { capacity_ = DEFAULT_CAPACITY; }
    T* oldElem = elem_;
    elem_ = new T[capacity_ *= 2];
    for (unsigned i=0; i < _size; ++i) { elem_[i] = oldElem[i]; }
    delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink()
{
    if (capacity_ < DEFAULT_CAPACITY || size_ > capacity_/4) { return; }
    T* oldElem = elem_;
    elem_ = new T[capacity_ /= 2];
    for (unsigned i=0; i<size_; ++i) { elem_[i] = oldElem[i]; }
    delete[] oldElem;
}