cmake_minimum_required(VERSION 3.29)
project(1lab)

project(1lab LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Ptrs)
include_directories(Structures)

add_executable(1lab
        Ptrs/ControllBlock.h
        Ptrs/SharedPtr.h
        Ptrs/UniqPtr.h
        Ptrs/WeakPtr.h
        Structures/DynamicArray.h
        Structures/LinkedList.h
        Structures/myDynamicArray.h
        Structures/myLinkedList.h
        Structures/timer.h
        listTests.h
        main.cpp
        tests.h
        z.cpp
        listTests.cpp
        tests.cpp
        Structures/timer.cpp)
