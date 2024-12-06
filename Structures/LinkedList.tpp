#pragma once

#include "LinkedList.h"

template <typename T>
LinkedList<T>::Node::Node(const T& value) : val(value), next(nullptr) {}

template <typename T>
LinkedList<T>::Node::Node(const T value, std::shared_ptr<Node> h) : val(value), next(h) {}

template <typename T>
LinkedList<T>::LinkedList() : size(0), head(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : size(list.size) {
    std::shared_ptr<Node> cur = list.head;
    while (cur != nullptr) {
        append(cur->val);
        cur = cur->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        del();
    }
    size = 0;
}

template <typename T>
T& LinkedList<T>::get(size_t index) {
    std::shared_ptr<Node> q = head;
    for (size_t i = 0; i < index && i < size; ++i) {
        q = q->next;
    }
    return q->val;
}

template <typename T>
T& LinkedList<T>::getFirst() {
    return head->val;
}

template <typename T>
T& LinkedList<T>::getLast() {
    std::shared_ptr<Node> q = head;
    while (q->next) {
        q = q->next;
    }
    return q->val;
}

template <typename T>
T& LinkedList<T>::operator[](size_t index) const {
    return const_cast<LinkedList<T>*>(this)->get(index);
}

template <typename T>
void LinkedList<T>::prepend(T item) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>(Node(item, head));
    if (!head) {
        head = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::append(T item) {
    std::shared_ptr<Node> newNode = std::make_shared<Node>(Node(item, nullptr));
    if (head) {
        std::shared_ptr<Node> q = head;
        while (q->next) {
            q = q->next;
        }
        q->next = newNode;
    } else {
        head = newNode;
    }
    size++;
}

template <typename T>
void LinkedList<T>::printFirst() {
    std::cout << head->val << "\n";
}

template <typename T>
void LinkedList<T>::show() {
    std::shared_ptr<Node> q = head;
    while (q) {
        std::cout << q->val << " ";
        q = q->next;
    }
    std::cout << "\n";
}

template <typename T>
LinkedList<T>* LinkedList<T>::getSubList(size_t startIndex, size_t endIndex) {
    auto* newList = new LinkedList<T>();
    std::shared_ptr<Node> q = head;
    for (size_t i = 0; i <= endIndex; i++) {
        if (i >= startIndex) {
            newList->append(q->val);
        }
        q = q->next;
    }
    return newList;
}

template <typename T>
size_t LinkedList<T>::getLength() {
    return size;
}

template <typename T>
LinkedList<T> LinkedList<T>::map(T func(T& item)) {
    LinkedList<T> newList;
    std::shared_ptr<Node> q = head;
    while (q) {
        newList.append(func(q->val));
        q = q->next;
    }
    return newList;
}

template <typename T>
void LinkedList<T>::del() {
    if (head) {
        head = head->next;
        size--;
    }
}

template <typename T>
T LinkedList<T>::reduce(T func(T& item1, T& item2), T item) {
    std::shared_ptr<Node> q = head;
    while (q) {
        item = func(q->val, item);
        q = q->next;
    }
    return item;
}

template <typename T>
LinkedList<T>::Iterator::Iterator(std::shared_ptr<Node> hw) : h(hw) {}

template <typename T>
T LinkedList<T>::Iterator::operator*() {
    return h->val;
}

template <typename T>
bool LinkedList<T>::Iterator::hasNext() const {
    return h->next != nullptr;
}

template <typename T>
T LinkedList<T>::Iterator::operator++(T) {
    if (!hasNext()) {
        throw std::out_of_range("No more elements to iterate over");
    }
    h = h->next;
    return h->val;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const {
    return Iterator(head);
}
