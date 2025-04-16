#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> arr;
    void heapify(vector<int>& arr, int index, int size) 
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int ViolatedNode = index;

        if (left < size && arr[ViolatedNode] < arr[left])
            ViolatedNode = left;
        if (right < size && arr[ViolatedNode] < arr[right])
            ViolatedNode = right;

        if (ViolatedNode != index) {
            swap(arr[index], arr[ViolatedNode]);
            heapify(arr, ViolatedNode, size);
        }
    }

   

public:
    MaxHeap() {}

    void buildHeap(vector<int>& arr, int size)
    {
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(arr, i, size);
        }
    }
    void Insert(int element) 
    {
        arr.push_back(element);
        buildHeap(arr, arr.size());
    }

    void removeElement(int element) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == element) {
                swap(arr[i], arr[arr.size() - 1]);
                arr.pop_back();
                buildHeap(arr, arr.size());
                break;
            }
        }
    }
    int ExtractMaxElement()
    {
        if (arr.size() == 0)
            return -1;
        int MaxElement = arr[0];
        removeElement(arr[0]);
        return MaxElement;
    }
    int ExtractMinElement()
    {
        if (arr.size() == 0)
            return -1;
        int MinElement = arr[0];
        for (int i = 0;i < arr.size();i++)
        {
            if (MinElement > arr[i])
                MinElement = arr[i];
        }
        removeElement(MinElement);
        return MinElement;
    }

    void print() {
        for (auto& elem : arr) 
        {
            cout << elem << ' ';
        }
        cout << "\n---------------------------" << endl;
    }

    void sort() {
        int size = arr.size();
        buildHeap(arr, size);
        for (int i = size - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, 0, i);
        }
    }

};


class PriorityQueue {
private:
    vector<pair<int, int>> queue; 
    MaxHeap heap; 

    void maintainHeap() {
        heap = MaxHeap();
        for (auto& p : queue) {
            heap.Insert(p.first); 
        }
    }

public:
    void insertWithPriority(int element, int priority) {
        queue.emplace_back(priority, element); 
        maintainHeap(); 
    }

    int extractHighestPriority() {
        if (queue.empty()) 
            return -1; 
        int maxPriority = heap.ExtractMaxElement();
        for (auto it = queue.begin(); it != queue.end(); ++it) {
            if (it->first == maxPriority) {
                int extractedElement = it->second;
                queue.erase(it); 
                return extractedElement; 
            }
        }
        return -1;
    }


};

int main()
{
    MaxHeap Heap;
    Heap.Insert(1);
    Heap.Insert(2);
    Heap.Insert(3);
    Heap.Insert(5);
    Heap.Insert(1);
    Heap.print();

    cout << Heap.ExtractMaxElement() << endl;
    cout << "After Extracting the Max \n";
    Heap.print();

    cout << Heap.ExtractMinElement() << endl << endl;
    cout << "After Extracting the Min \n";
    Heap.print();

    cout << "After Heap sorting \n";
    Heap.sort();
    Heap.print();

    cout << endl << endl;

    PriorityQueue PQueue;
    PQueue.insertWithPriority(3, 5);
    PQueue.insertWithPriority(4, 2);
    PQueue.insertWithPriority(6, 9);

    cout << PQueue.extractHighestPriority() << endl;
    cout << PQueue.extractHighestPriority() << endl;
    cout << PQueue.extractHighestPriority() << endl;


    
}


