//#include "SharedPtr.h"

// Реализация методов SharedPtr

template<typename T>
void SharedPtr<T>::release() {
    if (block) {
        block->minusRefCount();
        if (block->rRefCount() == 0) {
            delete obj;
            obj = nullptr;
            if (block->rWeakCount() == 0) {
                delete block;
                block = nullptr;
            }
        }
    }
}

template<typename T>
SharedPtr<T>::SharedPtr() : obj(nullptr), block(nullptr) {}

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr) : obj(ptr), block(new ControllBlock<T>(true, ptr)) {}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) noexcept : obj(other.obj), block(other.block) {
    if (block) {
        block->plusRefCount();
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept : obj(other.obj), block(other.block) {
    other.obj = nullptr;
    other.block = nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr(const T&& object) : obj(new T(object)), block(new ControllBlock<T>(true)) {}

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr, ControllBlock<T>* blk) : obj(ptr), block(blk) {
    if (block) {
        block->plusRefCount();
    }
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) {
    if (this != &other) {
        release();
        obj = other.obj;
        block = other.block;
        if (block) {
            block->plusRefCount();
        }
    }
    return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
        release();
        obj = other.obj;
        block = other.block;
        other.obj = nullptr;
        other.block = nullptr;
    }
    return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(WeakPtr<T>& ptr) noexcept {
    if (block != ptr.block) {
        release();
        block = ptr.block;
        if (block) {
            obj = block->getData();
            block->plusRefCount();
        } else {
            obj = nullptr;
        }
    }
    return *this;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const T&& object) {
    release();
    obj = new T(object);
    block = new ControllBlock<T>(true);
    return *this;
}

template<typename T>
T* SharedPtr<T>::get() const {
    return obj;
}

template<typename T>
T& SharedPtr<T>::operator*() {
    return *obj;
}

template<typename T>
T& SharedPtr<T>::operator[](size_t index) const {
    return obj[index];
}

template<typename T>
const T& SharedPtr<T>::operator->() const {
    return *obj;
}

template<typename T>
T& SharedPtr<T>::operator->() {
    return *obj;
}

template<typename T>
SharedPtr<T>::operator bool() const noexcept {
    return obj != nullptr;
}

template<typename T>
ControllBlock<T>* SharedPtr<T>::openBlock() {
    return block;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    release();
}

// Реализация функций make_shared

template<typename T>
SharedPtr<T> make_shared(T obj) {
    T* _Q = new T(obj);
    return SharedPtr<T>(_Q);
}

template<class Cl, typename... Args>
SharedPtr<Cl> make_shared(Args&&... args) {
    Cl* newP = new Cl{std::forward<Args>(args)...};
    return SharedPtr<Cl>(newP);
}

template<typename T>
template<typename U>
SharedPtr<T>::SharedPtr(U* ptr) : obj(ptr), block(new ControllBlock<U>()) {
    if (ptr) {
        block->shared_count = 1;
    }
}

template<typename T>
template<typename U>
SharedPtr<T>::SharedPtr(const SharedPtr<U>& other) : obj(other.obj), block(other.block) {
    if (block) {
        block->shared_count++;
    }
}

template<typename T>
template<typename U>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<U>& other) {
    if ((void*)this != (void*)&other) {
        release();
        obj = other.obj;
        block = other.block;
        if (block) {
            block->shared_count++;
        }
    }
    return *this;
}
