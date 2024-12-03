#include "radixSort.h"

void countSortForRadix(int *arr, int n, int exp)
{
    int* output = new int[n];
    int count[10] = {0};
    for(int i = 0; i < n; i++)
    {
        count[(arr[i] / exp) % 10]++;
    }
    for(int i = 1; i < 10; i++)
    {
        count[i] += count[i-1];
    }

    for(int i = n-1; i >= 0; --i)
    {
        output[count[(arr[i] / exp) % 10]-1] = arr[i];
        count[(arr[i] / exp ) % 10]--;
    }
    for(int i = 0; i < n; ++i)
    {
        arr[i] = output[i];
    }
    delete[] output;
}
void radixSort(int* arr, int n, int max)
{
    for(int exp = 1; exp <= max; exp *= 10)
    {
        countSortForRadix(arr, n, exp);
    }
}