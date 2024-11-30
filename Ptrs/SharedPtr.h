#pragma once

template<typename T>
class WeakPtr;
#include <vector>
#include "ControllBlock.h"
#include <memory>
#include <iostream>
#include <initializer_list>
template<typename T>
class SharedPtr{
private:
    friend class WeakPtr<T>;
    T* obj;
    ControllBlock<T>* block = nullptr;
    void release() ;
public:
    SharedPtr() ;
    explicit SharedPtr(T* ptr) ;

    SharedPtr& operator = (T* ptr) = delete;

    SharedPtr(const SharedPtr& other) noexcept ;

    SharedPtr(SharedPtr&& other) noexcept ;

    SharedPtr& operator=(WeakPtr<T>& ptr) noexcept {
        if (block && block != ptr.block) {
            block->minusRefCount();
            block = ptr.block;
            block->plusRefCount();
        }
        return *this;
    }
    SharedPtr(T* ptr, ControllBlock<T>* blk);
//
//    template<typename U>
    SharedPtr(const T&& object);

    SharedPtr& operator = (const SharedPtr& other) {
        if (this != &other) {
            release();
            obj = other.obj;
            block = other.block;
            if (block) {
                block->plusRefCount();
            }
        }
        return *this;
    }
    T& operator *() {
        return *obj;
    }

    const T& operator->() const { return *obj; }
    T& operator->() { return *obj; }

    SharedPtr& operator = (SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            obj = other.obj;
            block = other.block;
            other.obj = nullptr;
            other.block = nullptr;
        }
        return *this;
    }

    T* get() const ;

    ~SharedPtr() ;

    operator bool() const noexcept {
        return obj != nullptr;
    }

    ControllBlock<T>* openBlock() ;

    T& operator[](size_t index) const {
        return obj[index];
    }

};

template<typename T>
SharedPtr<T> make_shared(T obj) ;

template<class Cl, typename... Args>
SharedPtr<Cl> make_shared(Args&&... args) ;