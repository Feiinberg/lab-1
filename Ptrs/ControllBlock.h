

template<typename T>
class ControllBlock {
private:
    T* data;
    std::size_t ref_count = 0;
    std::size_t weak_count = 0;
public:
//    ControllBlock() : ref_count(0), weak_count(0), data(new T) {}
    ControllBlock() : ref_count(0), weak_count(0), data(nullptr) {}
    ControllBlock(bool is_shr) : ref_count(is_shr ?1 :0), weak_count(is_shr ?0 :1) {}
    ControllBlock(bool is_shr, T* data) : data(data), ref_count(is_shr ?1 :0), weak_count(is_shr ?0 :1) {}
    T& operator ->(){
        return *data;
    }
    void reset(T* newData){
        data = newData;
    }
    std::size_t rRefCount() {
        return ref_count;
    }
    std::size_t rWeakCount() {
        return weak_count;
    }
    
    void plusRefCount() noexcept {
        ++ref_count;
    }
    void minusRefCount() noexcept {
        if (ref_count > 0 ) {
            --ref_count;
        }
    }
    void plusWeakCount() noexcept {
        ++weak_count;
    }
    void minusWeakCount() noexcept {
        if (weak_count > 0) {
            --weak_count;
        }
    }
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
