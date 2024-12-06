#pragma once
//#include "WeakPtr.h"

template<typename T>
void WeakPtr<T>::release() {
    if (block) {
        block->minusWeakCount();
        if (block->rRefCount() + block->rWeakCount() == 0) {
            delete block;
            block = nullptr;
        }
    }
}

template<typename T>
WeakPtr<T>::WeakPtr() noexcept : block(new ControllBlock<T>(false)) {}

template<typename T>
WeakPtr<T>::WeakPtr(const WeakPtr& other) noexcept {
    if (this != &other) {
        block = other.block;
        block->plusWeakCount();
    }
}

template<typename T>
WeakPtr<T>::WeakPtr(SharedPtr<T>& ptr) {
    if (block != ptr.block) {
        block = ptr.block;
        block->plusWeakCount();
    }
}

template<typename T>
WeakPtr<T>::WeakPtr(T* el) : block(new ControllBlock<T>(false, el)) {}

template<typename T>
WeakPtr<T>::WeakPtr(T el) : block(new ControllBlock<T>(false, &el)) {}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& other) noexcept {
    if (block != other.block) {
        block->minusWeakCount();
        block = other.block;
        block->plusWeakCount();
    }
    return *this;
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(SharedPtr<T>& ptr) noexcept {
    if (block && block != ptr.block) {
        block->minusWeakCount();
        block = ptr.block;
        block->plusWeakCount();
    }
    return *this;
}

template<typename T>
WeakPtr<T>::~WeakPtr() {
    release();
}
