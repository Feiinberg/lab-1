
#pragma once
#include "Ptrs/UniqPtr.h"
#include <cassert>
//#include "WeakPtr.h"
#include "tests/listTests.h"
bool testOperatorAssigment() ;
struct Node {
    SharedPtr<Node> next;
//    Node* prev;
    
    Node(const std::shared_ptr<Node>& nextNode)
        : next(nextNode) {}
    Node(): next(SharedPtr<Node>()){}
};


struct NodeH {
    WeakPtr<Node> next;
    NodeH(const WeakPtr<Node>& nextNode)
        : next(nextNode) {}
    NodeH(): next(WeakPtr<Node>()) {}
    
};

bool testCircleList() ;

int functional_tests_shrdptr() ;;

int functional_tests_unqptr() ;



