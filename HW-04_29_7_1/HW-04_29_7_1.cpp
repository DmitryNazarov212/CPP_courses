#include <mutex>
#include <cassert>
#include <iostream>

struct Node
{
    int value;
    Node* next;
    std::mutex node_mutex; // Лучше хранить мьютекс прямо в узле

    Node(int val) : value(val), next(nullptr) {}
};

class FineGrainedQueue
{
    Node* head;
    std::mutex queue_mutex;

public:
    FineGrainedQueue() : head(nullptr) {}

    ~FineGrainedQueue() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void insertIntoMiddle(int value, int pos)
    {
        Node* newNode = new Node(value);

        std::unique_lock<std::mutex> qlock(queue_mutex);
        if (!head) {
            head = newNode;
            return;
        }

        Node* current = head;
        qlock.unlock();

        int currentPos = 1;

        while (current->next != nullptr && currentPos < pos)
        {
            std::unique_lock<std::mutex> currentLock(current->node_mutex);
            Node* next = current->next;

            std::unique_lock<std::mutex> nextLock(next->node_mutex);

            if (current->next != next) {
                continue;
            }

            currentLock.unlock();
            current = next;
            currentPos++;
        }

        std::lock_guard<std::mutex> currentLock(current->node_mutex);
        newNode->next = current->next;
        current->next = newNode;
    }
};
