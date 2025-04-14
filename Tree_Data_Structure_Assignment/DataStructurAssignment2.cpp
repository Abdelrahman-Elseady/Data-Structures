#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <vector>
using namespace std;

// class item
class item
{
protected:
    string itemname;
    string category;
    int price;
public:
    item() {
        itemname = ' '; category = ' '; price = 0;
    }

    item(string itemname, string category, int price)
        : itemname(itemname), category(category), price(price) {}

    bool operator<(const item& other) {
        return price < other.price;
    }

    bool operator>(const item& other) {
        return price > other.price;
    }

    bool operator==(const item& other) {
        return (itemname == other.itemname && category == other.category && price == other.price) ;
    }

    friend ostream& operator<<(ostream& out, const item& i) {
        out << i.itemname << ' ' << i.category << ' ' << i.price;
        return out;
    }

    void print() {
        cout << itemname << ' ' << category << ' ' << price << endl;
    }
};

class itembyname : public item {
public:
    itembyname() : item("", "", 0) {}

    itembyname(string itemname, string category, int price) : item(itemname, category, price) {}

    bool operator<(const itembyname& other) const {
        return itemname < other.itemname;
    }

    bool operator>(const itembyname& other) const {
        return itemname > other.itemname;
    }
};

// binary search tree
template <class T>
class Node {
public:
    T key;
    Node<T>* right, * left;

    Node() {
        left = right = NULL;
    }

    Node(const T& k, Node* r = NULL, Node* l = NULL) {
        key = k;
        right = r;
        left = l;
    }
};

template <class T>
class BST {
private:
    Node<T>* root;
public:
    BST() {
        root = NULL;
    }

    bool isEmpty() {
        return(!root);
    }

    T* search(T element) {
        Node<T>* nd = root;
        while (nd) {
            if (element == nd->key)return &(nd->key);
            else if (element > nd->key)nd = nd->right;
            else nd = nd->left;
        }
        return 0;
    }

    Node<T>** findNode(T element) {
        Node<T>** ptrNd = &root;
        while (*ptrNd) {
            if (element == (*ptrNd)->key)return ptrNd;
            else if (element > (*ptrNd)->key)ptrNd = &((*ptrNd)->right);
            else ptrNd = &((*ptrNd)->left);
        }
    }

    void insert(T element) {
        Node<T>* nd = root, * prev = NULL;
        while (nd) {
            prev = nd;
            if (element > nd->key)nd = nd->right;
            else nd = nd->left;
        }
        if (!root)root = new Node<T>(element);
        else if (element > prev->key)prev->right = new Node<T>(element);
        else prev->left = new Node<T>(element);
    }

    void remove(Node<T>*& nd) {
        Node<T>* temp = nd, * prev;
        if (nd->right == NULL && nd->left == NULL) {
            nd = NULL;
        }
        else if (nd->right == NULL) {
            nd = nd->left;
        }
        else if (nd->left == NULL) {
            nd = nd->right;
        }
        else {
            prev = temp;
            temp = temp->right;
            while (temp->left) {
                prev = temp;
                temp = temp->left;
            }
            nd->key = temp->key;
            if (prev == nd)prev->right = temp->right;
            else prev->left = temp->right;
        }
        delete temp;
    }

    void remove(T element) {
        remove(*(findNode(element)));
    }

    void traversal(Node<T>* nd) {
        if (nd != NULL) {
            traversal(nd->left);
            cout << nd->key << '\n';
            traversal(nd->right);
        }
    }

    void print() {
        traversal(root);
    }

    void dTraversal(Node<T>* nd) {
        if (nd != NULL) {
            dTraversal(nd->right);
            cout << nd->key << '\n';
            dTraversal(nd->left);
        }
    }

    void dPrint() {
        dTraversal(root);
    }

    friend void readItems(istream& input, BST<T>& tree) {
        int count;
        input >> count;

        string itemName, category;
        int price;

        for (int i = 0; i < count; ++i) {
            getline(input >> ws, itemName);
            getline(input >> ws, category);
            input >> price;
            
            tree.insert(T(itemName, category, price));
        }
    }
};

// AVL tree
template<typename T>
class AVLNode {
public:
    T key;
    AVLNode* left;
    AVLNode* right;
    int height;
};

template<typename T>
class AVLTrees {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    AVLNode<T>* newNode(T key) {
        AVLNode<T>* node = new AVLNode<T>();
        node->key = key;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return node;
    }

    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    int getBalanceFactor(AVLNode<T>* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    AVLNode<T>* insertNode(AVLNode<T>* node, T key) {
        if (node == nullptr)
            return newNode(key);
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (key < node->left->key)
                return rightRotate(node);
            else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balanceFactor < -1) {
            if (key > node->right->key)
                return leftRotate(node);
            else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    AVLNode<T>* nodeWithMinimumValue(AVLNode<T>* node) {
        AVLNode<T>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLNode<T>* deleteNode(AVLNode<T>* root, T key) {
        if (root == nullptr)
            return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLNode<T>* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                AVLNode<T>* temp = nodeWithMinimumValue(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balanceFactor = getBalanceFactor(root);
        if (balanceFactor > 1) {
            if (getBalanceFactor(root->left) >= 0)
                return rightRotate(root);
            else {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(root->right) <= 0)
                return leftRotate(root);
            else {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
    }

    void inOrderSmall(AVLNode<T>* node) {
        if (node == nullptr)
            return;
        inOrderSmall(node->left);
        cout << node->key << endl;
        inOrderSmall(node->right);
    }

    void inOrderBig(AVLNode<T>* node) {
        if (node == nullptr)
            return;
        inOrderBig(node->right);
        cout << node->key << endl;
        inOrderBig(node->left);
    }

public:
    AVLTrees() : root(nullptr) {}

    void insert(T key) {
        root = insertNode(root, key);
    }

    void remove(T key) {
        root = deleteNode(root, key);
    }

    void printInOrderSmall() {
        cout << "Inordersmall traversal of the AVL tree is \n";
        inOrderSmall(root);
        cout << endl;
    }

    void printInOrderBig() {
        cout << "Inorderbig traversal of the AVL tree is \n";
        inOrderBig(root);
        cout << endl;
    }

    friend void readItems(istream& input, AVLTrees<T>& tree) {
        int count;
        input >> count;

        string itemName, category;
        int price;

        for (int i = 0; i < count; ++i) {
            getline(input >> ws, itemName);
            getline(input >> ws, category);
            input >> price;

            tree.insert(T(itemName, category, price));
        }
    }
};

// class MaxHeap
template <class T>
class MaxHeap {
protected:
    vector<T> arr;

    virtual void heapify(vector<T>& arr, int index, int size) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int max = index;

        if (left < size && arr[max] < arr[left])
            max = left;
        if (right < size && arr[max] < arr[right])
            max = right;

        if (max != index) {
            swap(arr[index], arr[max]);
            heapify(arr, max, size);
        }
    }

    virtual void buildHeap(vector<T>& arr, int size) {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(arr, i, size);
        }
    }

public:
    MaxHeap() {}

    void addElement(const T& element) {
        arr.push_back(element);
        buildHeap(arr, arr.size());
    }

    void removeElement(const T& element) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == element) {
                swap(arr[i], arr[arr.size() - 1]);
                arr.pop_back();
                buildHeap(arr, arr.size());
                break;
            }
        }
    }

    void print() const {
        for (const auto& elem : arr) {
            cout << elem << endl;
        }
        cout << "---------------------------" << endl;
    }

    void sort() {
        int size = arr.size();
        buildHeap(arr, size);
        for (int i = size - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, 0, i);
        }
    }

    friend void readItems(istream& input, MaxHeap<T>& tree) {
        int count;
        input >> count;

        string itemName, category;
        int price;

        for (int i = 0; i < count; ++i) {
            getline(input >> ws, itemName);
            getline(input >> ws, category);
            input >> price;

            tree.addElement(T(itemName, category, price));
        }
    }
};

// class MinHeap
template <class T>
class MinHeap : public MaxHeap<T> {
protected:
    void heapify(vector<T>& arr, int index, int size) override {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int min = index;

        if (left < size && arr[min] > arr[left])
            min = left;
        if (right < size && arr[min] > arr[right])
            min = right;

        if (min != index) {
            swap(arr[index], arr[min]);
            heapify(arr, min, size);
        }
    }

    void buildHeap(vector<T>& arr, int size) override {
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(arr, i, size);
        }
    }

    friend void readItems(istream& input, MinHeap<T>& tree) {
        int count;
        input >> count;

        string itemName, category;
        int price;

        for (int i = 0; i < count; ++i) {
            getline(input >> ws, itemName);
            getline(input >> ws, category);
            input >> price;

            tree.addElement(T(itemName, category, price));
        }
    }
};

int main()
{
    cout << "Choose a tree data structure :\n";
    cout << "1- Binary Search Tree\n";
    cout << "2- AVL Tree\n";
    cout << "3- Heap\n";
    int x =  0; cin >> x;
    if (x == 1) {
        BST<item> tree;
        BST<itembyname> treebyname;
        while (x) {
            cout << "Choose an operation :\n";
            cout << "1-Add item data\n2-Remove item data\n3-Display the item data normally\n";
            cout << "4-Display all the items sorted by their name ascending\n5-Display all the items sorted by their name descending\n";
            cout << "6-Display all the items sorted by their prices ascending\n7-Display all the items sorted by their prices descending\n";
            cout << "8-Read the items from a file\nEnter zero to null\n";
            cin >> x;
            if (x == 1) {
                cout << "Enter the item name, its category and its price respectivly\n";
                string name;
                string cat;
                int price;
                cin >> name >> cat >> price;
                tree.insert(item(name, cat, price));
                treebyname.insert(itembyname(name, cat, price));
            }
            else if (x == 2) {
                cout << "Enter the item name, its category and its price respectivly\n";
                string name;
                string cat;
                int price;
                cin >> name >> cat >> price;
                tree.remove(item(name, cat, price));
                treebyname.remove(itembyname(name, cat, price));
            }
            else if (x == 3) tree.print();
            else if (x == 4) treebyname.print();
            else if (x == 5) treebyname.dPrint();
            else if (x == 6) tree.print();
            else if (x == 7) tree.dPrint();
            else if (x == 8) {
                ifstream file("items.txt");
                if (file.is_open()) {
                    readItems(file, tree);
                    file.close();
                }
                else {
                    cerr << "Can't open this file!!";
                    return 1;
                }

                ifstream file2("items.txt");
                if (file2.is_open()) {
                    readItems(file2, treebyname);
                    file2.close();
                }
                else {
                    cerr << "Can't open this file!!";
                    return 1;
                }
            }
        }
    }
    else if(x == 2){
        AVLTrees<item> tree2;
        AVLTrees<itembyname> treebyname2;
        while (x) {
            cout << "Choose an operation :\n";
            cout << "1-Add item data\n2-Remove item data\n3-Display the item data normally\n";
            cout << "4-Display all the items sorted by their name ascending\n5-Display all the items sorted by their name descending\n";
            cout << "6-Display all the items sorted by their prices ascending\n7-Display all the items sorted by their prices descending\n";
            cout << "8-Read the items from a file\nEnter zero to null\n";
            cin >> x;
            if (x == 1) {
                cout << "Enter the item name, its category and its price respectivly\n";
                string name;
                string cat;
                int price;
                cin >> name >> cat >> price;
                tree2.insert(item(name, cat, price));
                treebyname2.insert(itembyname(name, cat, price));
            }
            else if (x == 2) {
                cout << "Enter the item name, its category and its price respectivly\n";
                string name;
                string cat;
                int price;
                cin >> name >> cat >> price;
                tree2.remove(item(name, cat, price));
                treebyname2.remove(itembyname(name, cat, price));
            }
            else if (x == 3) tree2.printInOrderSmall();
            else if (x == 4) treebyname2.printInOrderSmall();
            else if (x == 5) treebyname2.printInOrderBig();
            else if (x == 6) tree2.printInOrderSmall();
            else if (x == 7) tree2.printInOrderBig();
            else if (x == 8) {
                ifstream file("items.txt");
                if (file.is_open()) {
                    readItems(file, tree2);
                    file.close();
                }
                else {
                    cerr << "Can't open this file!!";
                    return 1;
                }

                ifstream file2("items.txt");
                if (file2.is_open()) {
                    readItems(file2, treebyname2);
                    file2.close();
                }
                else {
                    cerr << "Can't open this file!!";
                    return 1;
                }
            }
        }
    }
    else if (x == 3) {
        MaxHeap<item> maxheap;
        MaxHeap<itembyname> maxheapByName;
        MinHeap<item> minheap;
        MinHeap<itembyname> minheapByName;
        while (true) {
            cout << "Choose an operation :\n";
            cout << "1-Add item data\n2-Remove item data\n3-Display the item data normally\n";
            cout << "4-Display all the items sorted by their name ascending\n5-Display all the items sorted by their name descending\n";
            cout << "6-Display all the items sorted by their prices ascending\n7-Display all the items sorted by their prices descending\n";
            cout << "8-Read the items from a file\nEnter zero to null\n";
            cin >> x;
            if (x == 0) break;
            if (x == 1) {
                cout << "Enter the item name, its category and its price respectively\n";
                string name;
                string cat;
                int price;
                cin >> name >> cat >> price;
                maxheap.addElement(item(name, cat, price));
                maxheapByName.addElement(itembyname(name, cat, price));
                minheap.addElement(item(name, cat, price));
                minheapByName.addElement(itembyname(name, cat, price));
            }
            else if (x == 2) {
                cout << "Enter the item name, its category and its price respectively\n";
                string name;
                string cat;
                int price;
                cin >> name >> cat >> price;
                maxheap.removeElement(item(name, cat, price));
                maxheapByName.removeElement(itembyname(name, cat, price));
                minheap.removeElement(item(name, cat, price));
                minheapByName.removeElement(itembyname(name, cat, price));
            }
            else if (x == 3) maxheap.print();
            else if (x == 5) {
                minheapByName.sort();
                minheapByName.print();
            }
            else if (x == 4) {
                maxheapByName.sort();
                maxheapByName.print();
            }
            else if (x == 7) {
                minheap.sort();
                minheap.print();
            }
            else if (x == 6) {
                maxheap.sort();
                maxheap.print();
            }
            else if (x == 8) {
                ifstream file("items.txt");
                if (file.is_open()) {
                    readItems(file, maxheap);
                    file.close();
                }
                else {
                    cerr << "Can't open this file!!";
                    return 1;
                }

                ifstream file2("items.txt");
                if (file2.is_open()) {
                    readItems(file2, maxheapByName);
                    file2.close();
                }
                else {
                    cerr << "Can't open this file!!";
                    return 1;
                }

                ifstream file3("items.txt");
                if (file3.is_open()) {
                    readItems(file3, minheap);
                    file3.close();
                }
                else {
                    cerr << "Can't open this file!!";
                    return 1;
                }

                ifstream file4("items.txt");
                if (file4.is_open()) {
                    readItems(file4, minheapByName);
                    file4.close();
                }
                else {
                    cerr << "Can't open this file!!";
                    return 1;
                }
            }
        }
    }
}
