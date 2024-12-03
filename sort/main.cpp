#include <iostream>
#include <chrono>

#include "countSort/counrSort.h"
#include "radixSort/radixSort.h"
#include "bucket/bucket.h"
#include "bubbleSort/bubbleSort.h"
#include "insertion/insertionSort.h"
#include "mergeSort/mergeSort.h"
#include "selectionSort/selectionSort.h"
#include "TimSort/timSort.h"
#include "quickSort/quickSort.h"
using namespace std;

int MaxValue(const int *arr, const int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
int main() {
    int array[] = {2,4,1,5,2,6,1,6,3,4};
    const int size = std::size(array);
    int max = MaxValue(array, size);
    std::vector<int>arr = { 1, 3, 5, 8, 5, 3 };
    int n = arr.size();

    auto start = chrono::high_resolution_clock::now();
    countSort(array, size, max);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Count "<<duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    radixSort(array, size, max);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Radix "<<duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    bucketSort(array, size, max);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Bucket "<<duration.count() << endl;

    start = chrono::high_resolution_clock::now();
     bubbleSort(array, size);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Bubble "<<duration.count() << endl;

    start = chrono::high_resolution_clock::now();
     insertionSort(array, size);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Insertion "<<duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    selectionSort(array, size);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Selection "<<duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    timSort(array, size);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Timing "<<duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    quickSort(array, 0, size - 1);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Quick "<<duration.count() << endl;

    start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, n-1);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout <<"Merge "<<duration.count() << endl;

    for (const int i : array)
    {
        cout << array[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    return 0;
}
