#include <iostream>
using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node<T>* next;

    Node( T newData) {
        data=newData;
        next= nullptr;
    }
};

template<typename T>
class CircularLinkedList {
private:
    Node<T>* head;
    int size;

public:
    CircularLinkedList()   {
        head=nullptr;
        size=0;

    }

    void insertAtHead(const T& element) {
        Node<T>* newNode = new Node<T>(element);
        if (!head) {
            head = newNode;
            newNode->next = head;
        } else {
            newNode->next = head->next;
            head->next = newNode;
        }
        size++;
    }

    void insertAtTail( T element) {
        Node<T>* newNode = new Node<T>(element);
        if (!head) {
            head = newNode;
            newNode->next = head;
        } else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
        size++;
    }

    void insertAt( T element, int index) {
        if (index < 0 || index > size) {
            cout << "Invalid index." << endl;
            return;
        }
        if (index == 0) {
            insertAtHead(element);
        } else if (index == size) {
            insertAtTail(element);
        } else {
            Node<T>* newNode = new Node<T>(element);
            Node<T>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
            size++;
        }
    }

    void removeAtHead() {
        if (!head) {
            return; // Nothing to remove
        }
        Node<T>* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        if (temp == head) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* firstNode = head->next;
            temp->next = firstNode;
            delete head;
            head = firstNode;
        }
        size--;
    }


    void removeAtTail() {
        if (!head) {
            return;
        }
        Node<T>* temp = head;
        Node<T>* prev = nullptr;
        while (temp->next != head) {
            prev = temp;
            temp = temp->next;
        }
        if (prev) {
            prev->next = head;
            delete temp;
        } else {
            delete head;
            head = nullptr;
        }
        size--;
    }

    void removeAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index." << endl;
            return;
        }
        if (index == 0) {
            removeAtHead();
        } else if (index == size - 1) {
            removeAtTail();
        } else {
            Node<T>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            Node<T>* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            size--;
        }
    }

    T retrieveAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index." << endl;
            return T();
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    void replaceAt(T newElement, int index) {
        if (index < 0 || index >= size) {
            cerr << "Invalid index." << endl;
            return;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        temp->data = newElement;
    }


    bool isEmpty() const {
        return (head == nullptr);
    }

    void print() {
        Node<T> *temp=head;
        if (isEmpty()) {
            cout << "Linked list is empty." << endl;
            return;
        }
       else{
           cout<<temp->data<<" ";
           while(temp->next!=head){
               temp=temp->next;
               cout<<temp->data<<" ";

           }
           cout<<endl;



       }
    }
    int linkedListSize() const {
        int count = 0;
        if (head == nullptr) {
            return count;
        }
        Node<T>* temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);
        return count;
    }
    bool isItemAtEqual( T element, int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index." << endl;
            return false;
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data == element;
    }
    void swap(int firstItemIdx, int secondItemIdx) {
        if (firstItemIdx < 0 || firstItemIdx >= size || secondItemIdx < 0 || secondItemIdx >= size) {
            cerr << "Invalid indices." << endl;
            return;
        }
        if (firstItemIdx == secondItemIdx) {
            return;
        }

        Node<T>* prevFirst = nullptr;
        Node<T>* currFirst = head;
        for (int i = 0; i < firstItemIdx; i++) {
            prevFirst = currFirst;
            currFirst = currFirst->next;
        }

        Node<T>* prevSecond = nullptr;
        Node<T>* currSecond = head;
        for (int i = 0; i < secondItemIdx; i++) {
            prevSecond = currSecond;
            currSecond = currSecond->next;
        }


        if (currFirst->next != currSecond) {

            if (prevFirst) {
                prevFirst->next = currSecond;
            } else {
                head = currSecond;
            }

            if (prevSecond) {
                prevSecond->next = currFirst;
            } else {
                head = currFirst;
            }


            Node<T>* temp = currFirst->next;
            currFirst->next = currSecond->next;
            currSecond->next = temp;
        } else {

            if (prevFirst) {
                prevFirst->next = currSecond;
            } else {
                head = currSecond;
            }

            currFirst->next = currSecond->next;
            currSecond->next = currFirst;


            prevSecond = currSecond;
            currFirst = currSecond->next;
        }
    }




    bool isExist( T value) {
        Node<T>* temp = head;
        while (temp != nullptr) {
            if (temp->data == value) {
                return true;
            }
            temp = temp->next;
            if (temp == head) {
                break;
            }
        }
        return false;
    }


    void clear() {
        while (head != nullptr) {
            removeAtHead();
        }
    }







};

int main() {


    CircularLinkedList<int> list;
    list.insertAtHead(10);
    list.insertAt(20, 1);
    list.insertAt(30,2);
    list.insertAtTail(40);

    cout << "List contents: ";
    list.print();
   cout<< list.linkedListSize()<<endl;
//   list.removeAtHead();
//   list.removeAtTail();
//    list.print();
  list.swap(2,3);
    list.print();
    cout<<list.isExist(50)<<endl;
    cout<<list.isItemAtEqual(20,5)<<endl;
//   cout<< list.retrieveAt(8);

//    CircularLinkedList<char>list;

//    list.insertAtHead('a');
//    list.insertAt('b',1);
//    list.insertAt('c',2);
//    list.insertAt('z',3);
//    list.insertAtTail('d');
//    cout<< list.linkedListSize()<<endl;
//    list.print();
//    list.swap(1,4);
//    list.print();
//   cout<< list.linkedListSize()<<endl;
//   list.removeAt(3);
//    list.print();





    return 0;
}
