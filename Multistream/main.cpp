#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <chrono>
#include <future>
#include <vector>
#include <algorithm>

using namespace std;

#define PART_SIZE 500000
#define RAND_ARR_SIZE 20000000 // ~100 mb

void print(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int*& arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int*& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge_to_file(const int* arr1, const int* arr2, int sz1, int sz2)
{
    fstream temp;
    temp.open("temp_1_file.txt", fstream::out | std::ofstream::trunc);

    if (temp.is_open())
    {
        int i = 0, j = 0;

        while (i < sz1 && j < sz2) {
            if (arr1[i] < arr2[j])
                temp << arr1[i++] << ' ';
            else
                temp << arr2[j++] << ' ';
        }

        while (i < sz1)
            temp << arr1[i++] << ' ';

        while (j < sz2)
            temp << arr2[j++] << ' ';

        temp.close();
        cout << "Data written to temp_1_file.txt" << endl; // Debug output
    }
    else {
        cerr << "Failed to open temp_1_file.txt for writing!" << endl;
    }
}

void merge_files()
{
    fstream res;
    fstream temp1;
    fstream temp2;

    temp1.open("temp_1_file.txt", fstream::in);
    res.open("res_file.txt", fstream::in);
    temp2.open("temp_2_file.txt", fstream::out | ofstream::trunc); // open and clear

    if (!temp1.is_open() || !temp2.is_open() || !res.is_open()) {
        cerr << "Failed to open files for merging!" << endl;
        return;
    }

    int temp1_value;
    int res_value;

    temp1 >> temp1_value;
    res >> res_value;
    while (!temp1.eof() && !res.eof()) {
        if (temp1_value <= res_value) {
            temp2 << temp1_value << ' ';
            temp1 >> temp1_value;
        }
        else {
            temp2 << res_value << ' ';
            res >> res_value;
        }
    }

    while (!res.eof()) {
        temp2 << res_value << ' ';
        res >> res_value;
    }

    while (!temp1.eof()) {
        temp2 << temp1_value << ' ';
        temp1 >> temp1_value;
    }

    temp1.close();
    temp2.close();
    res.close();

    // Проверяем, что temp_2_file.txt не пуст
    temp2.open("temp_2_file.txt", fstream::in);
    if (temp2.peek() == std::ifstream::traits_type::eof()) {
        cerr << "temp_2_file.txt is empty!" << endl;
        temp2.close();
        return;
    }
    temp2.close();

    // Копируем результат в res_file.txt
    if (!filesystem::copy_file("temp_2_file.txt", "res_file.txt",
        filesystem::copy_options::overwrite_existing))
        cerr << "Failed to copy temp_2_file.txt to res_file.txt!" << endl;
    else
        cout << "Data copied to res_file.txt" << endl; // Debug output
}

int read_part_arr(fstream& fs, int*& arr)
{
    arr = new int[PART_SIZE];
    int i;
    for (i = 0; i < PART_SIZE; i++) {
        if (fs.eof()) break; // Прерываем цикл, если достигнут конец файла
        fs >> arr[i];
    }

    if (i == 0) {
        delete[] arr;
        return 0;
    }

    cout << "Read " << i << " elements from file." << endl; // Debug output
    return i;
}

void sort_part(int* arr, int size) {
    quickSort(arr, 0, size - 1);
}

void sort_func(const string& filename) {
    fstream fs;
    fs.open(filename, fstream::in);

    if (fs.is_open())
    {
        vector<future<void>> futures;
        vector<int*> parts;

        while (!fs.eof())
        {
            int* part_1 = nullptr;
            int* part_2 = nullptr;

            int size_1 = read_part_arr(fs, part_1);
            int size_2 = read_part_arr(fs, part_2);

            if (size_1 == 0 && size_2 == 0) {
                if (part_1) delete[] part_1;
                if (part_2) delete[] part_2;
                break;
            }

            if (size_1 > 0) {
                parts.push_back(part_1);
                futures.push_back(async(launch::async, sort_part, part_1, size_1));
            }
            if (size_2 > 0) {
                parts.push_back(part_2);
                futures.push_back(async(launch::async, sort_part, part_2, size_2));
            }

            // Ограничиваем количество потоков
            if (futures.size() >= 4) {
                for (auto& f : futures) {
                    f.get();
                }
                futures.clear();
            }
        }

        // Дожидаемся завершения всех потоков
        for (auto& f : futures) {
            f.get();
        }

        // Сливаем отсортированные части
        for (size_t i = 0; i < parts.size(); i += 2) {
            if (i + 1 < parts.size()) {
                merge_to_file(parts[i], parts[i + 1], PART_SIZE, PART_SIZE);
                merge_files();
            }
        }

        // Освобождаем память
        for (auto& part : parts) {
            delete[] part;
        }

        fs.close();
    }
    else {
        cerr << "Failed to open file: " << filename << endl;
    }
}

void write_rand_arr(const string& filename)
{
    fstream fs;

    srand(time(nullptr));
    int lef_border = -100;
    int range_len = 50000; // правая граница = range_len + left_border

    fs.open(filename, fstream::out | ofstream::trunc);
    if (fs.is_open())
    {
        for (int i = 0; i < RAND_ARR_SIZE; i++)
            fs << (lef_border + rand() % range_len) << ' ';

        fs.close();
        cout << "Random data written to " << filename << endl; // Debug output
    }
    else {
        cerr << "Failed to open file: " << filename << endl;
    }
}

int main(int argc, char const* argv[])
{
    string filename = "array_data.txt";

    write_rand_arr(filename);
    cout << "Generating data is done!" << endl;

    fstream res;
    res.open("res_file.txt", fstream::out | ofstream::trunc);
    res.close();

    auto start = chrono::high_resolution_clock::now();
    sort_func(filename);
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " sec" << endl;

    return 0;
}