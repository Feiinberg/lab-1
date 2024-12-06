#pragma once

#include "myDynamicArray.h"
#include <stdexcept>
#include <algorithm> // Для std::copy

template <typename T>
void myDynamicArray<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];
    std::copy(data, data + size, newData);
    delete[] data;
    data = newData;
}

template <typename T>
myDynamicArray<T>::myDynamicArray() : data(new T[1]), capacity(1), size(0) {}

template <typename T>
myDynamicArray<T>::myDynamicArray(const T* items, size_t capacity, size_t size)
        : capacity(capacity), size(size), data(new T[capacity]) {
    std::copy(items, items + size, data);
}

template <typename T>
myDynamicArray<T>::myDynamicArray(const myDynamicArray<T>& other)
        : capacity(other.capacity), size(other.size), data(new T[other.capacity]) {
    std::copy(other.data, other.data + other.size, data);
}

template <typename T>
myDynamicArray<T>::~myDynamicArray() {
    delete[] data;
}

template <typename T>
T& myDynamicArray<T>::getFirst() {
    if (size == 0) throw std::out_of_range("Array is empty");
    return data[0];
}

template <typename T>
T& myDynamicArray<T>::getLast() {
    if (size == 0) throw std::out_of_range("Array is empty");
    return data[size - 1];
}

template <typename T>
T& myDynamicArray<T>::get(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
myDynamicArray<T>* myDynamicArray<T>::getSubSequence(size_t start_i, size_t end_i) {
    if (start_i > end_i || end_i >= size) throw std::out_of_range("Invalid indices");
    return new myDynamicArray<T>(data + start_i, end_i - start_i + 1, end_i - start_i + 1);
}

template <typename T>
myDynamicArray<T>& myDynamicArray<T>::append(T item) {
    if (size == capacity) resize();
    data[size++] = item;
    return *this;
}

template <typename T>
myDynamicArray<T>& myDynamicArray<T>::prepend(T item) {
    if (size == capacity) resize();
    T* newData = new T[capacity];
    newData[0] = item;
    std::copy(data, data + size, newData + 1);
    delete[] data;
    data = newData;
    size++;
    return *this;
}

template <typename T>
myDynamicArray<T>& myDynamicArray<T>::insertAt(T item, size_t index) {
    if (index > size) throw std::out_of_range("Index out of range");
    if (size == capacity) resize();
    T* newData = new T[capacity];
    std::copy(data, data + index, newData);
    newData[index] = item;
    std::copy(data + index, data + size, newData + index + 1);
    delete[] data;
    data = newData;
    size++;
    return *this;
}

template <typename T>
void myDynamicArray<T>::show() const {
    for (size_t i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

template <typename T>
myDynamicArray<T>* myDynamicArray<T>::map(T (*func)(const T&)) const {
    auto* newArray = new myDynamicArray<T>();
    newArray->size = size;
    newArray->capacity = capacity;
    newArray->data = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        newArray->data[i] = func(data[i]);
    }
    return newArray;
}

template <typename T>
T myDynamicArray<T>::reduce(T (*func)(const T&, const T&), T initial) const {
    for (size_t i = 0; i < size; i++) {
        initial = func(initial, data[i]);
    }
    return initial;
}

template <typename T>
myDynamicArray<T>* myDynamicArray<T>::where(bool (*func)(const T&)) const {
    auto* filteredArray = new myDynamicArray<T>();
    for (size_t i = 0; i < size; i++) {
        if (func(data[i])) {
            filteredArray->append(data[i]);
        }
    }
    return filteredArray;
}

template <typename T>
T& myDynamicArray<T>::operator[](size_t index) {
    return get(index);
}

template <typename T>
myDynamicArray<T>::Iterator::Iterator(T* start, T* end) : current(start), end(end) {}

template <typename T>
bool myDynamicArray<T>::Iterator::hasNext() const {
    return current != end;
}

template <typename T>
T& myDynamicArray<T>::Iterator::operator*() {
    return *current;
}

template <typename T>
typename myDynamicArray<T>::Iterator& myDynamicArray<T>::Iterator::operator++() {
    if (current == end) throw std::out_of_range("No more elements");
    ++current;
    return *this;
}

template <typename T>
typename myDynamicArray<T>::Iterator myDynamicArray<T>::begin() const {
    return Iterator(data, data + size);
}
