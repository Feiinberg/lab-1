#pragma once
#include <utility> // Для std::forward

template<typename T>
class UniqPtr {
private:
    T* ptr;
public:
    explicit UniqPtr(T* ptr);
    UniqPtr();
    UniqPtr(const UniqPtr&) = delete;
    UniqPtr& operator=(const UniqPtr&) = delete;
    UniqPtr& operator=(const T&& object);
    UniqPtr(UniqPtr&& other) noexcept;
    UniqPtr(T&& other) noexcept;

    T* release();
    UniqPtr& operator=(UniqPtr&& other) noexcept;
    explicit operator bool() const noexcept;

    auto& operator=(UniqPtr& other) noexcept;

    ~UniqPtr();
    void reset();
    T& get() const;
    T& operator*();
};

template<typename T>
UniqPtr<T> make_uniq(T arg);

template <class Cl, typename... Args>
UniqPtr<Cl> make_uniq(Args&&... args);

// Подключение файла реализации
#include "Ptrs/Impl/UniqPtr.tpp"
