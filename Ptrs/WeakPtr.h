#pragma once

#include "SharedPtr.h"

template<typename T>
class WeakPtr {
private:
    friend class SharedPtr<T>;
    ControllBlock<T>* block;
    void release();

public:
    explicit WeakPtr() noexcept;

    WeakPtr(const WeakPtr& other) noexcept ;
    
    WeakPtr(SharedPtr<T>& ptr);
 
    WeakPtr(T* el);
    WeakPtr(T el);
    WeakPtr& operator=(const WeakPtr& other) noexcept {
        if (block != other.block) {
            block->minusWeakCount();
            block = other.block;
            block->plusWeakCount();
        }
        return *this;
    }
    
    WeakPtr& operator=(SharedPtr<T>& ptr) noexcept {
        if (block && block != ptr.block) {
            block->minusWeakCount();
            block = ptr.block;
            block->plusWeakCount();
        }
        return *this;
    }
    
    virtual~WeakPtr() ;
    
};

