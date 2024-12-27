#pragma once
#include "ControllBlock.h"
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>

// Forward declaration
template<typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
private:
    friend class WeakPtr<T>;
    T* obj;
    ControllBlock<T>* block = nullptr;

    void release(); // Уменьшение счетчиков ссылок и освобождение ресурсов

public:
    // Конструкторы
    SharedPtr();
    explicit SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& other) noexcept;
    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr(const T&& object);
    SharedPtr(T* ptr, ControllBlock<T>* blk);

    // Операторы присваивания
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    SharedPtr& operator=(WeakPtr<T>& ptr) noexcept;
    SharedPtr& operator=(const T&& object);
    SharedPtr& operator=(T* ptr) = delete;

    // Доступ к объекту
    T* get() const;
    T& operator*();
    T& operator[](size_t index) const;
    const T& operator->() const;
    T& operator->();

    explicit operator bool() const noexcept;

    // Вспомогательные методы
    ControllBlock<T>* openBlock();

    // Деструктор
    ~SharedPtr();

    template<typename U>
    SharedPtr(U* ptr);

    template<typename U>
    SharedPtr(const SharedPtr<U>& other);

    template<typename U>
    SharedPtr<T>& operator=(const SharedPtr<U>& other);
};

// Шаблонные функции make_shared
template<typename T>
SharedPtr<T> make_shared(T obj);

template<class Cl, typename... Args>
SharedPtr<Cl> make_shared(Args&&... args);

#include "Ptrs/Impl/SharedPtr.tpp"
