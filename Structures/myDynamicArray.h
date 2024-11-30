
#pragma once

#include <cstddef>
#include <iostream>

template<typename T>

class myDynamicArray {
private:
    T* data;
    size_t capacity;
    size_t size;
    void resize(){
        capacity *= 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        delete [] data;
        data = newData;
    }
public:
    myDynamicArray(): data(new T[1]), capacity(1), size(0) {}
    myDynamicArray(T* item, size_t capacity ,size_t size): capacity(capacity), size(size) {
        data = new T[capacity];
        memcpy(data, item, size * sizeof(T)); // size*sizeof(T)  вместо capscity
    }
    myDynamicArray(myDynamicArray<T>* pr_array) {
        data = new T[capacity];
        memcpy(data, pr_array->data, pr_array->size * sizeof(T));
        capacity = pr_array->capacity;
        size = pr_array->size;
    }
    
    T& getFirst() {
        return data[0];
    }
    T& getLast() {
        return data[size-1];
    }
    T& get(size_t index) {
        return data[index];
    }
    
    myDynamicArray<T>* getSubSequence(size_t start_i, size_t end_i) {
        myDynamicArray<T> *q = new myDynamicArray<T>;
        q->size = end_i-start_i+1;
        q->capacity = end_i-start_i+1;
        memcpy(q->data, data+start_i, (end_i-start_i+1)*sizeof(T));
        return q;
    }
    
    myDynamicArray<T> append(T item){
        if (size < capacity) {
            data[size] = item;
            size++;
        } else {
            resize();
            data[size++] = item;
        }
        return *this;
    }
    
    myDynamicArray<T> prepend(T item){
        T* newData = new T[capacity];
        if (size + 1 == capacity) {
            resize();
        }
        newData[0] = item;
        memcpy(newData+1, data, size*sizeof(T));
        size++;
        free(data);
        data = newData;
        return *this;
    }
    
    void show() {
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        printf("\n");
    }
    
    myDynamicArray<T> insertAt (T item, size_t index) {
        T* newData = new T[capacity];
        if (size + 1 == capacity) {
            resize();
        }
        newData[index] = item;
        memcpy(newData, data, (index)*sizeof(T));
        memcpy(newData+index+1, data+index, (size-index)*sizeof(T));
        data = newData;
        size++;
        return *this;
    }
    
    size_t getLength() {
        return size;
    }
    
    myDynamicArray<T>* map(T func(T& item)) {
        for (size_t i = 0; i < size; i++) {
            data[i] = func(data[i]);
        }
        return this;
    }
    
    T& reduce(T func(T& item1, T& item2), T& item) {
        for (size_t i = 0; i < size; i++) {
            item = func(data[i],item);
        }
        return item;
    }
    
    myDynamicArray<T>* where(bool func(T& item)) {
        myDynamicArray<T>* newData = new myDynamicArray<T>;
        newData->size = 0;
        newData->capacity = 1;
        for (size_t i = 0; i < size; i++){
            if (func(data[i])){
                newData = newData->append(data[i]);
            }
        }
        return newData;
    }

    
    T& operator[](size_t index) const {
        return get(index);
    }
    
    class Iterator {
    private:
        T* dt;
        const size_t size = size;
        size_t currentIndex;
    public:
        Iterator(T* cur): dt(cur), currentIndex(0){}
        
        bool hasNext() const {
            return currentIndex < size;
        }
        
        bool hasPreious() const {
            return currentIndex > 0;
        }
        
        T operator ++ (T){
            if (!hasNext()) {
                throw std::out_of_range("No more elements to iterate over");
            }
            currentIndex++;
            return dt[currentIndex];
        }
        
        T operator -- (T){
            if (!hasPreious()) {
                throw std::out_of_range("No less elements to iterate over");
            }
            currentIndex--;
            return dt[currentIndex];
        }
        
        T operator * (){
            return dt[currentIndex];
        }
        
    };
    
    Iterator begin() const {
        return Iterator(*this);
    }
    
    
};
