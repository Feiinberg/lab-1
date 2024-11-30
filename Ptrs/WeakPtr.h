
#pragma once
#include "SharedPtr.h"
template<typename T>
class WeakPtr {
private:
    friend class SharedPtr<T>;
    ControllBlock<T>* block;
    void release() {
        if (block) {
            block->minusWeakCount();
            if (block->rRefCount() + block->rWeakCount() == 0) {
                delete block;
                block = nullptr;
            }
        }
    }
public:
    explicit WeakPtr() noexcept : block(new ControllBlock<T>(false)) {}
    WeakPtr(const WeakPtr& other) noexcept {
        if (this != &other) {
            block = other.block;
            block->plusWeakCount();
        }
    }
    
    WeakPtr(SharedPtr<T>& ptr) {
        if (block != ptr.block) {
            block = ptr.block;
            block->plusWeakCount();
        }
    }
 
    WeakPtr(T* el): block(new ControllBlock<T>(false, el)) {}
    WeakPtr(T el): block(new ControllBlock<T>(false, &el)) {}
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
    
    virtual~WeakPtr() {
        release();
    }
    
};

