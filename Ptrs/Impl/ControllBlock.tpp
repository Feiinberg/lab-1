#include <stdexcept> // Для исключений (если понадобится)

template<typename T>
ControllBlock<T>::ControllBlock() : data(nullptr), ref_count(0), weak_count(0) {}

template<typename T>
ControllBlock<T>::ControllBlock(bool is_shr)
        : data(nullptr), ref_count(is_shr ? 1 : 0), weak_count(is_shr ? 0 : 1) {}

template<typename T>
ControllBlock<T>::ControllBlock(bool is_shr, T* data)
        : data(data), ref_count(is_shr ? 1 : 0), weak_count(is_shr ? 0 : 1) {}

template<typename T>
T& ControllBlock<T>::operator->() {
    if (!data) {
        throw std::runtime_error("Attempted to dereference a null pointer");
    }
    return *data;
}

template<typename T>
void ControllBlock<T>::reset(T* newData) {
    data = newData;
}

template<typename T>
std::size_t ControllBlock<T>::rRefCount() {
    return ref_count;
}

template<typename T>
std::size_t ControllBlock<T>::rWeakCount() {
    return weak_count;
}

template<typename T>
void ControllBlock<T>::plusRefCount() noexcept {
    ++ref_count;
}

template<typename T>
void ControllBlock<T>::minusRefCount() noexcept {
    if (ref_count > 0) {
        --ref_count;
    }
}

template<typename T>
void ControllBlock<T>::plusWeakCount() noexcept {
    ++weak_count;
}

template<typename T>
void ControllBlock<T>::minusWeakCount() noexcept {
    if (weak_count > 0) {
        --weak_count;
    }
}

template<typename T>
ControllBlock<T>::operator bool() const noexcept {
    return data != nullptr;
}
