
#pragma once
#include <vector>
template<typename T>
class UniqPtr {
private:
    T* ptr;
public:
    explicit UniqPtr(T* ptr);
    UniqPtr();
    UniqPtr(const UniqPtr &) = delete;
    UniqPtr& operator = (const UniqPtr&) = delete;
    UniqPtr& operator = (const T&& object) {
        reset();
        ptr = new T(object);
        return *this;
    }
    UniqPtr(UniqPtr&& other) noexcept;

    UniqPtr(T&& other) noexcept ;

    T* release() ;

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
    ~UniqPtr() ;

    void reset() ;

    T& get() const ;

    T& operator *() {
        return *ptr;
    }
};

template<typename T>
UniqPtr<T> make_uniq(T arg);

template <class Cl, typename... Args>
UniqPtr<Cl> make_uniq(Args&&... args) ;