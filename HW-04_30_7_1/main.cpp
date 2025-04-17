#include <future>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <memory>
#include <mutex> // Для mutex и condition_variable

// Явно укажем пространство имен std
using namespace std;

// Реализация BlockedQueue
template<typename T>
class BlockedQueue {
private:
    queue<T> q;
    mutex mtx;
    condition_variable cv;

public:
    BlockedQueue() = default; // Явно добавляем конструктор по умолчанию
    ~BlockedQueue() = default; // Явно добавляем деструктор

    void push(T item) {
        lock_guard<mutex> lock(mtx);
        q.push(item);
        cv.notify_one();
    }

    bool fast_pop(T& item) {
        lock_guard<mutex> lock(mtx);
        if (q.empty()) return false;
        item = q.front();
        q.pop();
        return true;
    }

    void pop(T& item) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this] { return !q.empty(); });
        item = q.front();
        q.pop();
    }
};

// Класс пула потоков
using task_type = function<void()>;

class ThreadPool {
public:
    ThreadPool();
    void start();
    void stop();
    void push_task(task_type f);
    void threadFunc(int qindex);

private:
    int m_thread_count;
    vector<thread> m_threads;
    vector<BlockedQueue<task_type>> m_thread_queues;
    int m_index;
};

ThreadPool::ThreadPool()
    : m_thread_count(thread::hardware_concurrency() != 0 ? thread::hardware_concurrency() : 4),
      m_thread_queues(m_thread_count), m_index(0) {}

void ThreadPool::start() {
    for (int i = 0; i < m_thread_count; i++) {
        m_threads.emplace_back(&ThreadPool::threadFunc, this, i);
    }
}

void ThreadPool::threadFunc(int qindex) {
    while (true) {
        task_type task_to_do;
        bool res = false;
        int i = 0;
        for (; i < m_thread_count; i++) {
            if (res = m_thread_queues[(qindex + i) % m_thread_count].fast_pop(task_to_do))
                break;
        }

        if (!res) {
            m_thread_queues[qindex].pop(task_to_do);
        }

        if (!task_to_do) {
            return;
        }

        task_to_do();
    }
}

void ThreadPool::stop() {
    for (int i = 0; i < m_thread_count; i++) {
        task_type empty_task;
        m_thread_queues[i].push(empty_task);
    }
    for (auto& t : m_threads) {
        t.join();
    }
}

void ThreadPool::push_task(task_type f) {
    int queue_to_push = m_index++ % m_thread_count;
    m_thread_queues[queue_to_push].push(f);
}

// Глобальный пул потоков
ThreadPool pool;

// Структура для отслеживания задач
struct TaskCounter {
    shared_ptr<promise<void>> prom;
    shared_ptr<int> counter;

    TaskCounter() : prom(make_shared<promise<void>>()), counter(make_shared<int>(1)) {}
};

// Функция быстрой сортировки
void quicksort(int* array, long left, long right, TaskCounter tc = TaskCounter()) {
    if (left >= right) {
        if (--(*tc.counter) == 0) {
            tc.prom->set_value();
        }
        return;
    }

    long left_bound = left;
    long right_bound = right;
    long middle = array[(left_bound + right_bound) / 2];

    do {
        while (array[left_bound] < middle) left_bound++;
        while (array[right_bound] > middle) right_bound--;

        if (left_bound <= right_bound) {
            swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);

    if (right_bound - left > 10000) {
        (*tc.counter)++; // Увеличиваем счетчик для новой подзадачи
        TaskCounter new_tc = tc; // Копируем указатели на promise и counter
        pool.push_task([array, left, right_bound, new_tc]() { // Явно захватываем переменные
            quicksort(array, left, right_bound, new_tc);
        });
        quicksort(array, left_bound, right, tc);
    } else {
        quicksort(array, left, right_bound, tc);
        quicksort(array, left_bound, right, tc);
    }
}

int main() {
    srand(0);
    long arr_size = 100000000;
    int* array = new int[arr_size];
    for (long i = 0; i < arr_size; i++) {
        array[i] = rand() % 500000;
    }

    time_t start, end;

    // Запускаем пул потоков
    pool.start();

    // Многопоточный запуск
    time(&start);
    TaskCounter tc;
    quicksort(array, 0, arr_size - 1, tc);
    tc.prom->get_future().wait(); // Ждем завершения всех подзадач
    time(&end);

    double seconds = difftime(end, start);
    printf("The time (multithreaded): %f seconds\n", seconds);

    // Проверка сортировки
    for (long i = 0; i < arr_size - 1; i++) {
        if (array[i] > array[i + 1]) {
            cout << "Unsorted" << endl;
            break;
        }
    }

    // Останавливаем пул
    pool.stop();

    // Перезаполняем массив
    for (long i = 0; i < arr_size; i++) {
        array[i] = rand() % 500000;
    }

    // Однопоточный запуск
    time(&start);
    quicksort(array, 0, arr_size - 1);
    time(&end);
    seconds = difftime(end, start);
    printf("The time (single-threaded): %f seconds\n", seconds);

    delete[] array;
    return 0;
}