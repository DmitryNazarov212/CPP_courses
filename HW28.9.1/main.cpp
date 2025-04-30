#include <future>
#include <chrono>
#include <iostream>
using namespace std;

void merge(int* arr, int l, int m, int r) {
    int nl = m - l + 1;
    int nr = r - m;

    int left[nl], right[nr];

    for (int i = 0; i < nl; i++)
        left[i] = arr[l + i];
    for (int j = 0; j < nr; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0;
    int k = l;
    while (i < nl && j < nr) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < nl) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < nr) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void merge_sort(int* arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    if (right - left > 10000) {
        auto left_future = async(launch::async, merge_sort, arr, left, mid);
        merge_sort(arr, mid + 1, right);
        left_future.wait();
    } else {
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
    }

    merge(arr, left, mid, right);
}

bool is_sorted(int* arr, long size) {
    for (long i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(0);
    long arr_size = 100000;
    int* arr = new int[arr_size];
    for (long i = 0; i < arr_size; i++) {
        arr[i] = rand() % 5000000;
    }

    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();
    merge_sort(arr, 0, arr_size - 1);
    end = chrono::high_resolution_clock::now();
    double seconds = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1e6;
    cout << "The time: " << seconds << " seconds\n";

    if (is_sorted(arr, arr_size)) {
        cout << "Sorted\n";
    } else {
        cout << "Unsorted\n";
    }

    delete[] arr;
    return 0;
}