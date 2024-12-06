#pragma once
#include <cstddef> // Для std::size_t

template<typename T>
class ControllBlock {
private:
    T* data;
    std::size_t ref_count;
    std::size_t weak_count;

public:
    ControllBlock();
    ControllBlock(bool is_shr);
    ControllBlock(bool is_shr, T* data);

    T& operator->();
    void reset(T* newData);

    std::size_t rRefCount();
    std::size_t rWeakCount();

    void plusRefCount() noexcept;
    void minusRefCount() noexcept;

    void plusWeakCount() noexcept;
    void minusWeakCount() noexcept;

    explicit operator bool() const noexcept;
};

#include "Ptrs/Impl/ControllBlock.tpp" // Подключение файла реализации
