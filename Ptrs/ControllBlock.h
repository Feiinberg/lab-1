#pragma once

#include <cstddef>

template<typename T>
class ControllBlock {
private:
    T* data;
    size_t ref_count = 0;
    size_t weak_count = 0;
public:
//    ControllBlock() : ref_count(0), weak_count(0), data(new T) {}
    ControllBlock() ;
    ControllBlock(bool is_shr) ;
    ControllBlock(bool is_shr, T* data);
    T& operator ->(){
        return *data;
    }
    void reset(T* newData);

    size_t rRefCount() ;

    size_t rWeakCount() ;

    void plusRefCount() noexcept;

    void minusRefCount() noexcept;

    void plusWeakCount() noexcept ;

    void minusWeakCount() noexcept ;

    explicit operator bool() const noexcept {
        return  data != nullptr;
    }
//    ~ControllBlock(){
//        if (ref_count+weak_count == 0) {
//            ref_count = 0;
//            weak_count = 0;
//            delete data;
//            data = nullptr;
//        }
//    }
};
