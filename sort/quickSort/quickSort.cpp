#include "quickSort.h"
void swapForQuickSort(int* a, int* b) // функция для смены местами двух значений
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition (int* arr, int low, int high)
{
    int pivot = arr[high];    // опорный элемент
    int i = (low - 1);  // индекс наименьшего элемента
    for (int j = low; j <= high - 1; j++)
    {
        // если текущий элемент меньше или равен опорнуму
        if (arr[j] <= pivot)
        {
            i++;    // увеличиваем индекс минимального элемента
            swapForQuickSort(&arr[i], &arr[j]);
        }
    }
    swapForQuickSort(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high); // индекс опорного элемента
        // ваш код, выпоняющий корректные рекурсивыне вызовы для правой и левой частей входного массива
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi, high);
    }
}