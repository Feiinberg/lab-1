#include <iostream>
#include "tests/tests.h"


int main() {

    testOperatorAssigment();
    testCircleList();
    functional_tests_shrdptr();
    functional_tests_unqptr();
    functional_tests_weakptr();
    testsLinked();


    return 0;
}
