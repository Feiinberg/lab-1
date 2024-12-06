#pragma once

#include <iostream>
#include "WeakPtr.h"

template <typename T>
class myLinkedList {
private:
    struct Node{
        T val;
        SharedPtr<Node> next;
        Node(const T& value);
        Node(const T& value, SharedPtr<Node> h);
    };
    SharedPtr<Node> head;
    size_t size;

public:
    myLinkedList();
    myLinkedList(const myLinkedList<T>& list);
    ~myLinkedList();

    T& get(size_t index);
    T& getFirst();
    T& getLast();
    T& operator[](size_t index) const;

    void append(T item);
    void prepend(T item);
    void printFirst();

    void show();
    myLinkedList<T>* getSubList(size_t startIndex, size_t endIndex);
    size_t getLength();
    myLinkedList<T> map(T func(T& item));
    void del();
    T reduce(T func(T& item1, T& item2), T item);

    class Iterator {
    private:
        SharedPtr<Node> h;
    public:
        Iterator(SharedPtr<Node> hw);
        T operator * ();
        bool hasNext() const;
        bool hasPreious() const;
        T operator ++ (int);
        T operator -- (int);
    };

    Iterator begin() const;
};

// Включаем файл с реализациями шаблонных функций
#include "Structures/Impl/myLinkedList.tpp"
