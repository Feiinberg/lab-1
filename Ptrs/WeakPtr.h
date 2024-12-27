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
    WeakPtr(const WeakPtr& other) noexcept;
    WeakPtr(SharedPtr<T>& ptr);
    WeakPtr(T* el);
    WeakPtr(T el);
    WeakPtr& operator=(const WeakPtr& other) noexcept;
    WeakPtr& operator=(SharedPtr<T>& ptr) noexcept;
    virtual ~WeakPtr();
    ControllBlock<T>* openBlock() const { return block; }
};

// Подключение файла реализации
#include "Ptrs/Impl/WeakPtr.tpp"
