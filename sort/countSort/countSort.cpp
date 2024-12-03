#include "counrSort.h"

void countSort(int* arr, const int n, const int max)
{
    const auto tempArray = new int[n];
    const auto freqArray = new int[max + 1];
    for (int i = 0; i <= max; i++)
    {
        freqArray[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        freqArray[arr[i]]++; //заполняем массив часотот
    }
    for (int i = 1; i <= max; i++)
    {
        freqArray[i] += freqArray[i - 1]; // складываем частоты
    }
    for (int i = n-1; i >= 0; i--)
    {
        tempArray[freqArray[arr[i]]-1] = arr[i]; //подставляем значение исзодного массива во временный, при чем ииспользуем накопившуюся частоту с вычетом 1
        freqArray[arr[i]]--; //уменьшаем индекс (накопившуюся частоту), т.е повторение
    }
    cout << endl;
    for (int i = 0; i < n; i++) //копируем отсортированный массив во входной
    {
        arr[i] = tempArray[i];
    }
    delete[]tempArray;
    delete[]freqArray;
   }
