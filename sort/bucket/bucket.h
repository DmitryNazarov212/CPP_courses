#pragma once

struct bucket {
    int count; // количество элементов в корзине
    int* data; // массив элементов корзины
};
int getExp(int value);
void countSortForBucket(int* arr, int n, int max);
void bucketSort(int* arr, int n, int max);