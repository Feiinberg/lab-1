#pragma once
#include <cstddef>
#include <stdexcept>
#include <iostream>

template<typename T>
class DynamicArray {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize();

public:
    DynamicArray();
    DynamicArray(T* item, size_t capacity, size_t size);
    DynamicArray(DynamicArray<T>* pr_array);

    T& getFirst();
    T& getLast();
    T& get(size_t index);

    DynamicArray<T>* getSubSequence(size_t start_i, size_t end_i);

    DynamicArray<T> append(T item);
    DynamicArray<T> prepend(T item);
    DynamicArray<T> insertAt(T item, size_t index);

    size_t getLength();

    DynamicArray<T>* map(T func(T& item));
    T& reduce(T func(T& item1, T& item2), T& item);
    DynamicArray<T>* where(bool func(T& item));

    void show();

    T& operator[](size_t index) const;

    class Iterator {
    private:
        T* dt;
        const size_t size;
        size_t currentIndex;

    public:
        Iterator(T* cur, size_t sz);

        bool hasNext() const;
        bool hasPrevious() const;

        T operator++(int);
        T operator--(int);
        T operator*();
    };

    Iterator begin() const;
};

#include "DynamicArray.tpp"
