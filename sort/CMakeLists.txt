cmake_minimum_required(VERSION 3.29)
project(Courses)

set(CMAKE_CXX_STANDARD 20)

add_executable(Courses main.cpp
        countSort/counrSort.h
        countSort/countSort.cpp
        radixSort/radixSort.cpp
        radixSort/radixSort.h
        bucket/bucket.h
        bucket/bucket.cpp
        bubbleSort/bubbleSort.h
        bubbleSort/bubbleSort.cpp
        insertion/insertionSort.h
        insertion/inserionSort.cpp
        mergeSort/mergeSort.cpp
        mergeSort/mergeSort.h
        selectionSort/selectionSort.cpp
        selectionSort/selectionSort.h
        TimSort/timSort.cpp
        TimSort/timSort.h
        quickSort/quickSort.cpp
        quickSort/quickSort.h
)
