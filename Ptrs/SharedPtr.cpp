#include "SharedPtr.h"
template<typename T>
void SharedPtr<T>::release() {
    if (block) {
        block->minusRefCount();
        if (block->rRefCount() == 0) {
            delete obj;
//                std::cout << "delete shared" << "\n";
            obj = nullptr;
            if (block->rWeakCount() == 0) {
                delete block;
//                    std::cout << "delete controll block" << "\n";
                block = nullptr;
            }
        }
    }
}

template<typename T>
SharedPtr<T>::SharedPtr() : obj(nullptr), block(nullptr){}

template<typename T>
 SharedPtr<T>::SharedPtr(T* ptr) : obj(ptr), block(new ControllBlock<T>(true, ptr)) {};

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) noexcept : obj(other.obj) {
    if (this != &other) {
        release();
        block = other.block;
        if (block) {
            block->plusRefCount();
        }
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : block(other.block) {
    if (this != &other) {
        release();
        block = other.block;
        other.obj = nullptr;
        other.block = nullptr;
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr, ControllBlock<T>* blk) : obj(ptr), block(blk) {
    if (block) {
        block->plusRefCount();
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(const T&& object): obj(new T(object)), block(new ControllBlock<T>(true)) {}

template<typename T>
T* SharedPtr<T>::get() const {
    return obj;
}
template<typename T>
SharedPtr<T>::~SharedPtr() {
    release();
}

template<typename T>
ControllBlock<T>* SharedPtr<T>::openBlock() {
    return block;
}

template<typename T>
SharedPtr<T> make_shared(T obj) {
    T* _Q = new T(obj);
    return SharedPtr<T>(_Q);
}

template<class Cl, typename... Args>
SharedPtr<Cl> make_shared(Args&&... args) {
    Cl* newP = new Cl{std::forward<Args>(args)...};
    SharedPtr<Cl> ptr(newP);
    return ptr;
}