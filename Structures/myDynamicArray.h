#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class myDynamicArray {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize();

public:
    // Конструкторы и деструктор
    myDynamicArray();
    myDynamicArray(const T* items, size_t capacity, size_t size);
    myDynamicArray(const myDynamicArray<T>& other);
    ~myDynamicArray();

    // Методы доступа
    T& getFirst();
    T& getLast();
    T& get(size_t index);

    // Получение подпоследовательности
    myDynamicArray<T>* getSubSequence(size_t start_i, size_t end_i);

    // Модификация массива
    myDynamicArray<T>& append(T item);
    myDynamicArray<T>& prepend(T item);
    myDynamicArray<T>& insertAt(T item, size_t index);

    // Печать
    void show() const;

    // Map, Reduce, Where
    myDynamicArray<T>* map(T (*func)(const T&)) const;
    T reduce(T (*func)(const T&, const T&), T initial) const;
    myDynamicArray<T>* where(bool (*func)(const T&)) const;

    // Оператор доступа
    T& operator[](size_t index);

    // Итератор
    class Iterator {
    private:
        T* current;
        T* end;

    public:
        Iterator(T* start, T* end);
        bool hasNext() const;
        T& operator*();
        Iterator& operator++();
    };

    Iterator begin() const;
};

#include "Impl/myDynamicArray.tpp"