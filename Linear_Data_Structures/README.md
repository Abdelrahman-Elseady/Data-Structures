## 📁 Included Structures

- `single_linked_list.cpp` — Singly Linked List  
- `double_linked_list.cpp` — Doubly Linked List  
- `circular_linked_list.cpp` — Circular Linked List  
- `stack.cpp` — Stack (using linked list)  
- `queue.cpp` — Queue (using linked list)  
- `skip_list.cpp` — Skip List (player ranking system)

---

## 📌 Linked List Implementations

Each linked list supports the following operations:

- `insertAtHead(elementType element)` : `void`  
- `insertAtTail(elementType element)` : `void`  
- `insertAt(elementType element, int index)` : `void`  
- `removeAtHead()` : `void`  
- `removeAtTail()` : `void`  
- `removeAt(int index)` : `void`  
- `retrieveAt(int index)` : `elementType`  
- `replaceAt(elementType newElement, int index)` : `void`  
- `isExist(elementType element)` : `bool`  
- `isItemAtEqual(elementType element, int index)` : `bool`  
- `swap(int firstItemIdx, int secondItemIdx)` : `void`  
- `isEmpty()` : `bool`  
- `linkedListSize()` : `int`  
- `clear()` : `void`  
- `print()` : `void`  

---

## 📌 Stack Implementation

Implemented using a linked list with the following operations:

- `push(elementType element)` : `void`  
- `pop()` : `elementType`  
- `top()` : `elementType`  
- `isEmpty()` : `bool`  
- `stackSize()` : `int`  
- `clear()` : `void`  
- `print()` : `void`  

---

## 📌 Queue Implementation

Also implemented using a linked list with the following operations:

- `enqueue(elementType element)` : `void`  
- `dequeue()` : `elementType`  
  > Returns and removes the front element  
- `first()` : `elementType`  
  > Returns the front element without removing it  
- `isEmpty()` : `bool`  
- `queueSize()` : `int`  
- `clear()` : `void`  
- `print()` : `void`  

---

## 📌 Priority Queue Implementation

Implemented using max heap with the following operations:

- `insertWithPriority(int element, int priority)` : `void`  
- `extractHighestPriority()` : `void`  

---

## 📌 Skip List Implementation

The Skip List is implemented to manage players' scores with efficient insert, search, and delete operations. It also supports persistence by reading from and writing to a file.

### ✅ Features:

- `insert(score, playerName)` : `void`  
  > Inserts a new player with the specified score.
  
- `remove(score)` : `void`  
  > Removes a player by score.
  
- `search(score)` : `Node*`  
  > Searches for a player by score.
  
- `getTopPlayers(N)` : `void`  
  > Displays the top `N` players with the highest scores.
  
- `updateScore(oldScore, newScore)` : `void`  
  > Updates a player's score.
  
- `loadPlayersFromFile(filename)` : `void`  
  > Loads players from a file.
  
- `savePlayersToFile(filename)` : `void`  
  > Saves the current list of players to a file.