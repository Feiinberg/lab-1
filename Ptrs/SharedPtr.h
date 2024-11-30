

template<typename T>
class WeakPtr;
#include <vector>
#include "ControllBlock.h"
#include <memory>
#include <iostream>
#include <initializer_list>
template<typename T>
class SharedPtr{
private:
    friend class WeakPtr<T>;
    T* obj;
    ControllBlock<T>* block = nullptr;
    void release() {
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
public:
    SharedPtr() : obj(nullptr), block(nullptr){}
    explicit SharedPtr(T* ptr) : obj(ptr), block(new ControllBlock<T>(true, ptr)) {};

    SharedPtr& operator = (T* ptr) = delete;

    SharedPtr(const SharedPtr& other) noexcept : obj(other.obj) {
        if (this != &other) {
            release();
            block = other.block;
            if (block) {
                block->plusRefCount();
            }
        }
    }
    SharedPtr(SharedPtr&& other) noexcept : block(other.block) {
        if (this != &other) {
            release();
            block = other.block;
            other.obj = nullptr;
            other.block = nullptr;
        }
    }
    SharedPtr& operator=(WeakPtr<T>& ptr) noexcept {
        if (block && block != ptr.block) {
            block->minusRefCount();
            block = ptr.block;
            block->plusRefCount();
        }
        return *this;
    }
    SharedPtr(T* ptr, ControllBlock<T>* blk) : obj(ptr), block(blk) {
        if (block) {
            block->plusRefCount();
        }
    }
//
//    template<typename U>
    SharedPtr(const T&& object): obj(new T(object)), block(new ControllBlock<T>(true)) {}
    SharedPtr& operator = (const T&& object) {
        release();
        obj = new T(object);
        block = new ControllBlock<T>(true);
        return *this;
    }
    SharedPtr& operator = (const SharedPtr& other) {
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
    T& operator *() {
        return *obj;
    }
    
    const T& operator->() const { return *obj; }
    T& operator->() { return *obj; }
    
    SharedPtr& operator = (SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            obj = other.obj;
            block = other.block;
            other.obj = nullptr;
            other.block = nullptr;
        }
        return *this;
    }

    T* get() const {
        return obj;
    }
    ~SharedPtr() {
        release();
    }
    explicit operator bool() const noexcept {
        return obj != nullptr;
    }
    
    ControllBlock<T>* openBlock() {
        return block;
    }
    T& operator[](size_t index) const {
        return obj[index];
    }

};

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
