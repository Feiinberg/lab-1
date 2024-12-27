#pragma once

//#include "UniqPtr.h"

template<typename T>
UniqPtr<T>::UniqPtr(T* ptr) : ptr(ptr) {}

template<typename T>
UniqPtr<T>::UniqPtr() : ptr(nullptr) {}

template<typename T>
UniqPtr<T>& UniqPtr<T>::operator=(const T&& object) {
    reset();
    ptr = new T(object);
    return *this;
}

template<typename T>
UniqPtr<T>::UniqPtr(UniqPtr&& other) noexcept : ptr(other.ptr) {
    if (this != &other) {
        other.ptr = nullptr;
    }
}

template<typename T>
UniqPtr<T>::UniqPtr(T&& other) noexcept {
    ptr = new T(other);
}

template<typename T>
T* UniqPtr<T>::release() {
    T* neW = ptr;
    ptr = nullptr;
    return neW;
}

template<typename T>
UniqPtr<T>& UniqPtr<T>::operator=(UniqPtr&& other) noexcept {
    if (this != &other) {
        reset();
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template<typename T>
UniqPtr<T>::operator bool() const noexcept {
    return ptr != nullptr;
}

template<typename T>
auto& UniqPtr<T>::operator=(UniqPtr& other) noexcept {
    if (ptr == other.ptr) {
        other.ptr = nullptr;
        return *this;
    }
    delete ptr;
    ptr = other.ptr;
    other.ptr = nullptr;
    return *this;
}

template<typename T>
UniqPtr<T>::~UniqPtr() {
    reset();
}

template<typename T>
void UniqPtr<T>::reset() {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
}

template<typename T>
T& UniqPtr<T>::get() const {
    return *ptr;
}

template<typename T>
T& UniqPtr<T>::operator*() {
    return *ptr;
}

template<typename T>
UniqPtr<T> make_uniq(T arg) {
    T* ptr = new T(arg);
    return UniqPtr<T>(ptr);
}

template <class Cl, typename... Args>
UniqPtr<Cl> make_uniq(Args&&... args) {
    Cl* newP = new Cl{std::forward<Args>(args)...};
    UniqPtr<Cl> ptr(newP);
    return ptr;
}

template<typename T>
template<typename U>
UniqPtr<T>::UniqPtr(U* ptr) : ptr(ptr) {}

template<typename T>
template<typename U>
UniqPtr<T>::UniqPtr(UniqPtr<U>&& other) noexcept {
    ptr = other.ptr;
    other.ptr = nullptr;
}

template<typename T>
template<typename U>
UniqPtr<T>& UniqPtr<T>::operator=(UniqPtr<U>&& other) noexcept {
    if ((void*)this != (void*)&other) {
        reset();
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}
