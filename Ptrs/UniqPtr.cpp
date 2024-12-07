#include "UniqPtr.h"

template<typename T>
UniqPtr<T>::UniqPtr(T* ptr) : ptr(ptr) {}

template<typename T>
UniqPtr<T>::UniqPtr(): ptr(nullptr) {}

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