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

// Linked list-based stack class
template <typename T>
class LinkedListStack {
private:
    Node<T>* head;
    int size;

public:
    LinkedListStack() : head(nullptr), size(0) {}

    // Push an element onto the stack
    void push(T element) {
        Node<T>* newNode = new Node<T>(element);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // Pop the top element from the stack and return it
    T pop() {
        if (isEmpty()) {
            throw out_of_range("Stack underflow");
        }
        Node<T>* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        size--;
        return value;
    }

    // Return the top element without removing it
    T top() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return head->data;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Get the size of the stack
    int stackSize() {
        return size;
    }

    // Clear the stack
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Print all elements in the stack
    void print() {
        Node<T>* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Destructor to clear the stack
    ~LinkedListStack() {
        clear();
    }
};


int main() {
    LinkedListStack<int> stack;

    // Push some elements onto the stack
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // Print the stack
    cout << "Stack after pushing elements: ";
    stack.print();

    // Get and print the top element
    cout << "Top element of the stack: " << stack.top() << endl;

    // Pop an element and print it
    cout << "Popped element: " << stack.pop() << endl;

    // Print the stack after popping an element
    cout << "Stack after popping an element: ";
    stack.print();

    // Check if the stack is empty
    if (stack.isEmpty()) {
        cout << "Stack is empty." << endl;
    } else {
        cout << "Stack is not empty." << endl;
    }

    // Clear the stack
    stack.clear();

    // Check if the stack is empty after clearing
    if (stack.isEmpty()) {
        cout << "Stack is empty after clearing." << endl;
    } else {
        cout << "Stack is not empty after clearing." << endl;
    }

    return 0;
}


