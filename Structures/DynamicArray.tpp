#pragma once
#include "DynamicArray.h"
#include <cstring>

template<typename T>
void DynamicArray<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template<typename T>
DynamicArray<T>::DynamicArray() : data(new T[1]), capacity(1), size(0) {}

template<typename T>
DynamicArray<T>::DynamicArray(T* item, size_t capacity, size_t size)
        : capacity(capacity), size(size) {
    data = new T[capacity];
    std::memcpy(data, item, size * sizeof(T));
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>* pr_array) {
    data = new T[pr_array->capacity];
    std::memcpy(data, pr_array->data, pr_array->size * sizeof(T));
    capacity = pr_array->capacity;
    size = pr_array->size;
}

template<typename T>
T& DynamicArray<T>::getFirst() {
    return data[0];
}

template<typename T>
T& DynamicArray<T>::getLast() {
    return data[size - 1];
}

template<typename T>
T& DynamicArray<T>::get(size_t index) {
    return data[index];
}

template<typename T>
DynamicArray<T>* DynamicArray<T>::getSubSequence(size_t start_i, size_t end_i) {
    DynamicArray<T>* q = new DynamicArray<T>;
    q->size = end_i - start_i + 1;
    q->capacity = end_i - start_i + 1;
    q->data = new T[q->capacity];
    std::memcpy(q->data, data + start_i, (end_i - start_i + 1) * sizeof(T));
    return q;
}

template<typename T>
DynamicArray<T> DynamicArray<T>::append(T item) {
    if (size < capacity) {
        data[size] = item;
        size++;
    } else {
        resize();
        data[size++] = item;
    }
    return *this;
}

template<typename T>
DynamicArray<T> DynamicArray<T>::prepend(T item) {
    if (size + 1 >= capacity) {
        resize();
    }
    T* newData = new T[capacity];
    newData[0] = item;
    std::memcpy(newData + 1, data, size * sizeof(T));
    delete[] data;
    data = newData;
    size++;
    return *this;
}

template<typename T>
DynamicArray<T> DynamicArray<T>::insertAt(T item, size_t index) {
    if (size + 1 >= capacity) {
        resize();
    }
    T* newData = new T[capacity];
    std::memcpy(newData, data, index * sizeof(T));
    newData[index] = item;
    std::memcpy(newData + index + 1, data + index, (size - index) * sizeof(T));
    delete[] data;
    data = newData;
    size++;
    return *this;
}

template<typename T>
size_t DynamicArray<T>::getLength() {
    return size;
}

template<typename T>
DynamicArray<T>* DynamicArray<T>::map(T func(T& item)) {
    for (size_t i = 0; i < size; i++) {
        data[i] = func(data[i]);
    }
    return this;
}

template<typename T>
T& DynamicArray<T>::reduce(T func(T& item1, T& item2), T& item) {
    for (size_t i = 0; i < size; i++) {
        item = func(data[i], item);
    }
    return item;
}

template<typename T>
DynamicArray<T>* DynamicArray<T>::where(bool func(T& item)) {
    DynamicArray<T>* newData = new DynamicArray<T>;
    for (size_t i = 0; i < size; i++) {
        if (func(data[i])) {
            newData->append(data[i]);
        }
    }
    return newData;
}

template<typename T>
void DynamicArray<T>::show() {
    for (size_t i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

template<typename T>
T& DynamicArray<T>::operator[](size_t index) const {
    return data[index];
}

template<typename T>
DynamicArray<T>::Iterator::Iterator(T* cur, size_t sz)
        : dt(cur), size(sz), currentIndex(0) {}

template<typename T>
bool DynamicArray<T>::Iterator::hasNext() const {
    return currentIndex < size;
}

template<typename T>
bool DynamicArray<T>::Iterator::hasPrevious() const {
    return currentIndex > 0;
}

template<typename T>
T DynamicArray<T>::Iterator::operator++(int) {
    if (!hasNext()) {
        throw std::out_of_range("No more elements to iterate over");
    }
    return dt[currentIndex++];
}

template<typename T>
T DynamicArray<T>::Iterator::operator--(int) {
    if (!hasPrevious()) {
        throw std::out_of_range("No less elements to iterate over");
    }
    return dt[--currentIndex];
}

template<typename T>
T DynamicArray<T>::Iterator::operator*() {
    return dt[currentIndex];
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() const {
    return Iterator(data, size);
}
