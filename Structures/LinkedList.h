#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class LinkedList {
private:
    struct Node {
        T val;
        std::shared_ptr<Node> next;

        Node(const T& value);
        Node(const T value, std::shared_ptr<Node> h);
    };

    std::shared_ptr<Node> head;
    size_t size;

public:
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();

    T& get(size_t index);
    T& getFirst();
    T& getLast();
    T& operator[](size_t index) const;

    void append(T item);
    void prepend(T item);

    void printFirst();
    void show();

    LinkedList<T>* getSubList(size_t startIndex, size_t endIndex);

    size_t getLength();

    LinkedList<T> map(T func(T& item));
    void del();

    T reduce(T func(T& item1, T& item2), T item);

    class Iterator {
    private:
        std::shared_ptr<Node> h;

    public:
        Iterator(std::shared_ptr<Node> hw);

        T operator*();
        bool hasNext() const;

        T operator++(T);
    };

    Iterator begin() const;
};

#include "Structures/Impl/LinkedList.tpp"
