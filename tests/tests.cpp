#include "Ptrs/UniqPtr.h"
#include <cassert>
//#include "WeakPtr.h"
#include "tests/listTests.h"
#include "tests.h"

bool testOperatorAssigment() {
    SharedPtr<int> p1(new int(5));
    WeakPtr<int> p2(p1);
    WeakPtr<int> p3(p2);
    WeakPtr<int> p4(p3);
    p2 = p4;
    return 0;
}





bool testCircleList() {
    Node node1;
    Node node2;
    NodeH node3;
    SharedPtr<Node> p1 = make_shared(node1);
    SharedPtr<Node> p2 = make_shared(node2);
    SharedPtr<NodeH> head = make_shared(node3);
    (*head).next = p1;
    (*p1).next = p2;
    (*p2).next = (*head).next;
    return 0;
}

int functional_tests_shrdptr() {
    // Test 1: Basic constructor and dereferencing
    SharedPtr<int> sp1(new int(10));
    assert(*sp1 == 10);
    assert(sp1.openBlock()->rRefCount() == 1);

    // Test 2: Copy constructor and use count
    SharedPtr<int> sp2 = sp1;
    assert(*sp2 == 10);
    assert(sp1.openBlock()->rRefCount() == 2);
    assert(sp2.openBlock()->rRefCount() == 2);

    // Test 3: Assignment operator
    SharedPtr<int> sp3;
    sp3 = sp2;
    assert(*sp3 == 10);
    assert(sp1.openBlock()->rRefCount() == 3);
    assert(sp3.openBlock()->rRefCount() == 3);

    // Test 4: Reset function
    sp3 = make_shared(20);
    assert(*sp3 == 20);
    assert(sp2.openBlock()->rRefCount() == 2);

    // Test 5: Polymorphic behavior (template constructor)
    SharedPtr<double> sp4(3.14);
    assert(*sp4 == 3.14);

    // Test 6: Bool operator and null pointer
    SharedPtr<int> sp_null;
    assert(!sp_null);
    sp_null = 100;
    assert(sp_null);
    assert(*sp_null == 100);

    return 0;
}


int functional_tests_unqptr() {
    // Test 1: Basic constructor and dereferencing
    UniqPtr<int> up1(10);
    assert(*up1 == 10);

//    // Test 2: Move constructor
    UniqPtr<int> up2 = std::move(up1);
    assert(!up1);  // up1 should now be null
    assert(*up2 == 10);

    // Test 3: Move assignment operator
    UniqPtr<int> up3;
    up3 = std::move(up2);
    assert(!up2);  // up2 should now be null
    assert(*up3 == 10);

    // Test 5: Release function
    int* raw_ptr = up3.release();
    assert(!up3);  // up3 should now be null
    assert(*raw_ptr == 10);
    delete raw_ptr;  // Manual cleanup needed after release

    return 0;
}



