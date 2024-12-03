#include "selectionSort.h"
void swapForSelection(int* a, int* b) // функция для смены местами двух значений
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int* arr, int size) {
    for (int i = 0; i < size; i++) { //прохождение по массиву
        int minIndex = i; //выставляем минимальный индекс
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) { //если следующий индекс больше минимального
                minIndex = j; // это минимальное число
            }
        }
        swapForSelection(&arr[i], &arr[minIndex]);
    }
}

