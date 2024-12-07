#include "ControllBlock.h"

template<typename T>
ControllBlock<T>::ControllBlock()  : ref_count(0), weak_count(0), data(nullptr) {}

template<typename T>
ControllBlock<T>::ControllBlock(bool is_shr) : ref_count(is_shr ?1 :0), weak_count(is_shr ?0 :1) {}

template<typename T>
ControllBlock<T>::ControllBlock(bool is_shr, T* data) : data(data), ref_count(is_shr ?1 :0), weak_count(is_shr ?0 :1) {}

template<typename T>
void ControllBlock<T>::reset(T* newData){
    data = newData;
}

template<typename T>
size_t ControllBlock<T>::rRefCount() {
    return ref_count;
}

template<typename T>
size_t ControllBlock<T>::rWeakCount() {
    return weak_count;
}

template<typename T>
void ControllBlock<T>::plusRefCount() noexcept {
    ++ref_count;
}

template<typename T>
void ControllBlock<T>::minusRefCount() noexcept {
    if (ref_count > 0 ) {
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