
#pragma once
#include <vector>
template<typename T>
class UniqPtr {
private:
    T* ptr;
public:
    explicit UniqPtr(T* ptr) : ptr(ptr) {}
    UniqPtr(): ptr(nullptr) {}
    UniqPtr(const UniqPtr &) = delete;
    UniqPtr& operator = (const UniqPtr&) = delete;
    UniqPtr& operator = (const T&& object) {
        reset();
        ptr = new T(object);
        return *this;
    }
    UniqPtr(UniqPtr&& other) noexcept : ptr(other.ptr) {
        if (this != &other) {
            other.ptr = nullptr;
        }
    }
    UniqPtr(T&& other) noexcept {
        ptr = new T(other);
    }
    T* release() {
        T* neW = ptr;
        ptr = nullptr;
        return neW;
    }
    UniqPtr& operator = (UniqPtr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    explicit operator bool() const noexcept {
        return ptr != nullptr;
    }
    
    auto& operator= (UniqPtr& other) noexcept {
        if (ptr == other.ptr) {
            other.ptr = nullptr;
            return *this;
        }
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    ~UniqPtr() {
        reset();
    }
    void reset() {
        if (ptr) {
            delete ptr;
            ptr = nullptr;
        }
    }
    T& get() const {
        return *ptr;
    }
    T& operator *() {
        return *ptr;
    }
};

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
