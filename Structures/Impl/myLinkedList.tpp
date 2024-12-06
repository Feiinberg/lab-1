
#pragma once

//#include "myLinkedList.h"

// Реализация методов Node
template <typename T>
myLinkedList<T>::Node::Node(const T& value) : val(value), next(nullptr) {}

template <typename T>
myLinkedList<T>::Node::Node(const T& value, SharedPtr<Node> h) : val(value), next(h) {}

// Реализация методов класса myLinkedList
template <typename T>
myLinkedList<T>::myLinkedList() : size(0), head(nullptr) {}

template <typename T>
myLinkedList<T>::myLinkedList(const myLinkedList<T>& list) : size(list.size) {
    SharedPtr<Node> cur = list.head;
    while (cur != nullptr) {
        push_back(cur->val);
        cur = cur->next;
    }
}

template <typename T>
myLinkedList<T>::~myLinkedList() {
    while (head.get()) {
        del();
    }
    size = 0;
}

template <typename T>
T& myLinkedList<T>::get(size_t index) {
    SharedPtr<Node> q = head;
    for (size_t i = 0; i < index && i < size; ++i) {
        q = q->next;
    }
    return q->val;
}

template <typename T>
T& myLinkedList<T>::getFirst() {
    return head->val;
}

template <typename T>
T& myLinkedList<T>::getLast() {
    SharedPtr<Node> q = head;  // Убедитесь, что q — это умный указатель, а не объект
    while (q && q->next) {  // Проверяем, что указатель валиден и что следующий элемент существует
        q = q->next;
    }
    return q->val;
}

template <typename T>
T& myLinkedList<T>::operator[](size_t index) const {
    return get(index);
}

template <typename T>
void myLinkedList<T>::prepend(T item) {
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

template <typename T>
void myLinkedList<T>::append(T item) {
    SharedPtr<Node> newNode = make_shared<Node>(Node(item));
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

template <typename T>
void myLinkedList<T>::printFirst() {
    myLinkedList<T> q = *this;
    std::cout << q.head->val << "\n";
}


template <typename T>
void myLinkedList<T>::show() {
    SharedPtr<Node> q = head;
    while (q.get() != nullptr) {
        std::cout << q.get()->val << " ";
        q = q.get()->next;
    }
    std::cout << "\n";
}

template <typename T>
myLinkedList<T>* myLinkedList<T>::getSubList(size_t startIndex, size_t endIndex) {
    SharedPtr<myLinkedList<T>> newList = myLinkedList();
    SharedPtr<Node> q = head;
    for (size_t i = 0; i <= endIndex; i++) {
        if (i >= startIndex) {
            newList->append(q->val);
        }
        q = q->next;
    }
    return newList;
}

template <typename T>
size_t myLinkedList<T>::getLength() {
    return size;
}

template <typename T>
myLinkedList<T> myLinkedList<T>::map(T func(T& item)) {
    SharedPtr<myLinkedList<T>> newList = myLinkedList();
    SharedPtr<Node> q = head;
    for (size_t i = 0; i <= size; i++) {
        newList->append(func(q->val));
        q = q->next;
    }
    return newList;
}

template <typename T>
void myLinkedList<T>::del() {
    if (head.get()) {
        SharedPtr<Node> q = head.get()->next;
        --size;
        head = q;
    }
}

template <typename T>
T myLinkedList<T>::reduce(T func(T& item1, T& item2), T item) {
    SharedPtr<Node> q = head;
    for (size_t i = 0; i < size; i++) {
        item = func(q->val, item);
        q = q->next;
    }
    return item;
}

// Реализация класса Iterator
template <typename T>
myLinkedList<T>::Iterator::Iterator(SharedPtr<Node> hw) : h(hw) {}

template <typename T>
T myLinkedList<T>::Iterator::operator* () {
    return h->val;
}

template <typename T>
bool myLinkedList<T>::Iterator::hasNext() const {
    return (h->next) != NULL;
}

template <typename T>
bool myLinkedList<T>::Iterator::hasPreious() const {
    return (h->prev) != NULL;
}

template <typename T>
T myLinkedList<T>::Iterator::operator++(int) {
    if (!hasNext()) {
        throw std::out_of_range("No more elements to iterate over");
    }
    h = h->next;
    return h->val;
}

template <typename T>
T myLinkedList<T>::Iterator::operator--(int) {
    if (!hasPreious()) {
        throw std::out_of_range("No less elements to iterate over");
    }
    h = h->prev;
    return h->val;
}

template <typename T>
typename myLinkedList<T>::Iterator myLinkedList<T>::begin() const {
    return Iterator(head);
}
