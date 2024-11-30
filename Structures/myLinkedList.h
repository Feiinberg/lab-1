
#pragma once
#include "WeakPtr.h"
template <typename T>
class myLinkedList {
private:
    struct Node{
        T val;
        SharedPtr<Node> next;
        Node(const T& value) : val(value), next(nullptr) {}
        Node(const T& value, SharedPtr<Node> h) : val(value), next(h) {}
    };
    SharedPtr<Node> head;
    size_t size;
public:
    myLinkedList(): size(0), head(nullptr) {}
    myLinkedList(const myLinkedList<T>& list): size(list.size) {
        SharedPtr<Node> cur = list.head;
        while (cur != nullptr) {
            push_back(cur->val);
            cur = cur->next;
        }
    }
    T& get(size_t index) {
        SharedPtr<Node> q = head;
        for (size_t i = 0; i < index && i < size; ++i) {
            q = q->next;
        }
        return q->val;
    }
    ~myLinkedList() {
        while (head.get()) {
            del();
        }
        size = 0;
    }
    T& getFirst() {
        return head->val;
    }
    T& getLast() {
        SharedPtr<Node> q = head;
        while (q->next) {
            q = q->next;
        }
    }
    T& operator[](size_t index) const {
        return get(index);
    }
    void append(T item) {
        SharedPtr<Node> newNode = make_shared<Node>(Node(item, head));
        if (head.get() == nullptr) {
            head = newNode;
            size++;
        } else {
            newNode.get()->next = head;
            head = newNode;
            size++;
        }
    }
    void prepend(T item) {
        SharedPtr<Node> newNode = make_shared<Node>(Node(item));//nullptr
        if (head.get()) {
            SharedPtr<Node> q = head;
            while ((q.get()->next).get() != nullptr) {
                q = q.get()->next;
            }
            q.get()->next = newNode;
            size++;
        } else {
            head = newNode;
            size++;
        }
    }
    
    void printFirst() {
        myLinkedList<T> q = *this;
        std::cout << q.head->val << "\n";
    }
    
    void show() {
        SharedPtr<Node> q = head;
        while (q.get() != nullptr) {
            std::cout << q.get()->val << " ";
            q = q.get()->next;
        }
        std::cout <<"\n";
    }
    
    myLinkedList<T>* getSubList(size_t startIndex, size_t endIndex) {
        SharedPtr<myLinkedList<T>> newList = myLinkedList();
        SharedPtr<Node> q = head;
        for (size_t i = 0; i <= endIndex; i++) {
            if (i >= startIndex) {
                newList->Append(q->val);
            }
            q = q->next;
        }
        return newList;
    }
    
    size_t getLength() {
        return size;
    }
    
    
    myLinkedList<T> map(T func(T& item)) {
        SharedPtr<myLinkedList<T>> newList = myLinkedList();
        SharedPtr<Node> q = head;
        for (size_t i = 0; i <= size; i++) {
            newList->append(func(q->val));
            q = q->next;
        }
        return newList;
    }
    void del() {
        if (head.get()) {
            SharedPtr<Node> q = head.get()->next;
            //вроде теряю controll block
            --size;
            head = q;
        }
    }
    
    T reduce(T func(T& item1, T& item2), T item) {
        SharedPtr<Node> q = head;
        for (size_t i = 0; i < size; i++) {
            item = func(q->val, item);
            q = q->next;
        }
        return item;
    }
    
    class Iterator {
    private:
        SharedPtr<Node> h;
    public:
        Iterator(SharedPtr<Node> hw): h(hw) {}
        
        T operator * (){
            return h->val;
        }
        
        bool hasNext() const {
            return (h->next) != NULL;
        }
        
        bool hasPreious() const {
            return (h->prev) != NULL;
        }
        
        T operator ++ (T){
            if (!hasNext()) {
                throw std::out_of_range("No more elements to iterate over");
            }
            h = h->next;
            return h->val;
        }
        
        T operator -- (T){
            if (!hasPreious()) {
                throw std::out_of_range("No less elements to iterate over");
            }
            h = h->prev;
            return h->val;
        }
    };
    
    Iterator begin() const {
        return Iterator(head);
    }
    
};
