#include <iostream>
#include <stdexcept>

using namespace std;

// Node structure for linked list
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

// Linked list-based queue class
template <typename T>
class LinkedListQueue {
private:
    Node<T>* front; // Pointer to the front of the queue
    Node<T>* tail;  // Pointer to the tail of the queue
    int size;

public:
    // Constructor initializes an empty queue
    LinkedListQueue() : front(nullptr), tail(nullptr), size(0) {}

    // Enqueue an element at the tail
    void enqueue(T element) {
        Node<T>* newNode = new Node<T>(element);
        if (isEmpty()) {
            front = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Dequeue the front element and return it
    T dequeue() {
        if (isEmpty()) {
            throw out_of_range("Queue underflow");
        }
        Node<T>* temp = front;
        T value = temp->data;
        front = front->next;
        if (front == nullptr) {
            tail = nullptr; // If queue becomes empty, set tail to nullptr
        }
        delete temp;
        size--;
        return value;
    }

    // Return the front element without removing it
    T first() {
        if (isEmpty()) {
            throw out_of_range("Queue is empty");
        }
        return front->data;
    }

    // Check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    // Get the size of the queue
    int queueSize() {
        return size;
    }

    // Clear the queue
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Print all elements in the queue
    void print() {
        Node<T>* current = front;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Destructor to clear the queue and prevent memory leaks
    ~LinkedListQueue() {
        clear();
    }
};


int main() {
    LinkedListQueue<int> queue;

    // Enqueue elements
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    // Print queue
    cout << "Queue: ";
    queue.print();  // Output: 10 20 30

    // Dequeue an element
    cout << "Dequeued element: " << queue.dequeue() << endl;  // Output: Dequeued element: 10

    // Print the front element
    cout << "Front element: " << queue.first() << endl;  // Output: Front element: 20

    // Check if the queue is empty
    cout << "Is the queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;  // Output: Is the queue empty? No

    // Print the size of the queue
    cout << "Queue size: " << queue.queueSize() << endl;  // Output: Queue size: 2

    // Clear the queue
    queue.clear();

    // Print queue after clearing
    cout << "Queue after clearing: ";
    queue.print();  // Output: Queue after clearing:

    return 0;
}
