#include "Structures/myLinkedList.h"
#include "LinkedList.h"
#include "tests/util/timer.h"

#include "listTests.h"

template<typename T>
void appendTest(T& list) {
    for (int i = 0; i < 5000; ++i) {
        list.append(i);

    }
}
template<typename T>
void eraseTest(T& list) {
    while (list.getLength() > 0) {
        list.del();
    }
}
template<typename T>
void prependTest(T& list) {
    for (int i = 0; i < 500000; ++i) {
        list.prepend(i);
    }
}

void testsLinked() {
    myLinkedList<int> q;
    std::cout << "myLinkedList" << "\n";

    std::cout << "prepend" << " ";
    timer(prependTest<myLinkedList<int>>, q);



    std::cout << "erase" << " ";
    timer(eraseTest<myLinkedList<int>>, q);

    std::cout << "append" << " ";
    timer(appendTest<myLinkedList<int>>, q);

    LinkedList<int> q_;
    std::cout << "LinkedList" << "\n";

    std::cout <<"prepend" << " ";
    timer(prependTest<LinkedList<int>>, q_);


    std::cout << "erase" << " ";
    timer(eraseTest<LinkedList<int>>, q_);

    std::cout <<"append" << " ";
    timer(appendTest<LinkedList<int>>, q_);
}