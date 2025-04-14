## Included Structures

- **Binary Search Tree (BST)**  
  Allows storing items sorted by price. Supports displaying items in ascending or descending order of price.

- **AVL Tree**  
  A self-balancing Binary Search Tree ensuring optimal search time by maintaining balance after each insertion/deletion.

- **Max Heap**  
  A complete binary tree where each parent node is greater than or equal to its children. Useful for sorting in descending order.

- **Min Heap**  
  A complete binary tree where each parent node is less than or equal to its children. Useful for sorting in ascending order.

---

## Features

- Add and remove items
- Display items in different orders (by name or price)
- Sort items using tree and heap structures
- Read item data from an external file
- Compare balanced and unbalanced tree behavior


---

## 📌 Functionalities

Each structure provides the following operations (where applicable):

- `insert(element)` : `void`  
- `remove(element)` : `void`  
- `displayInOrder()` : `void`  
- `displayDescending()` / `displayAscending()` : `void`  
- `sortByPrice()` : `void`  
- `sortByName()` : `void`  
- `loadFromFile(filename)` : `void`  