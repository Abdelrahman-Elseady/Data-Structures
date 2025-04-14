
#include <utility>
#include<stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

template <class T>

class Doule_Linked_List
{
private:
	struct Node
	{
		T item;
		Node* next;
		Node* prev;
	};
	Node* first;
	Node* last;
	int size;

public:
	Doule_Linked_List()
	{
		first = last = NULL;
		size = 0;
	}

	void insertAtHead(T element)
	{
		Node* newNode = new Node;
		newNode->item = element;
		if (first == NULL)
		{
			first = last = newNode;
			newNode->next = NULL;
			newNode->prev = NULL;
		}
		else
		{
			newNode->next = first;
			newNode->prev = NULL;
			first->prev = newNode;
			first = newNode;
		}
		size++;
	}
	void insertAtTail(T element)
	{
		Node* newNode = new Node;
		newNode->item = element;
		if (first == NULL)
		{
			first = last = newNode;
			newNode->next = NULL;
			newNode->prev = NULL;
		}
		else
		{
			last->next = newNode;
			newNode->prev = last;
			newNode->next = NULL;
			last = newNode;
		}
		size++;
	}
	void print()
	{
		Node* p = first;
		for (int i = 0; i < size; i++)
		{

			cout << p->item << " ";
			p = p->next;
			
		}
		cout << endl;
	}
	void insertAt(T element, int index)
	{

		if (index == 0)
			insertAtHead(element);

		else if (index == size)
			insertAtTail(element);

		else if (index > size || index < 0)
			cout << "Out of range" << endl;

		else
		{
			Node* newNode = new Node;
			newNode->item = element;
			//curr will point at the index-1 
			Node* curr = first;
			for (size_t i = 1; i < index; i++)
			{
				curr = curr->next;
			}
			newNode->next = curr->next;
			newNode->prev = curr;
			curr->next->prev = newNode;
			curr->next = newNode;
		}
		size++;
	}
	void removeAtHead()
	{
		if (size == 0)
			cout << "the list is empty\n";
		else
		{
			Node* curr = first;
			first = first->next;
			delete curr;
			
		}
		size--;
	}

	void removeAtTail()
	{
		
		if (size == 0)
			cout << "the list is empty\n";
		else if (size == 1)
			removeAtHead();
		else
		{
			Node* curr = last;
			last = last->prev;
			last->next = NULL;
			delete curr;
		}
		size--;
	}
	void removeAt(int index)
	{
		if (index >= size || index < 0)
		{
			cout << "can't remvoe because it is out of range" << endl;
			return;
		}

		else if (size == 1)
			removeAtHead();
		else
		{
			Node* curr = first->next, * prev = first;

			for (int i = 1; i < index; i++)
			{
				curr = curr->next;
				prev = prev->next;
			}
			prev->next = curr->next;
			curr->next->prev = prev;
			delete curr;
			size--;
		}
	}
	bool isEmpty()
	{
		if (size == 0)
			return true;
		else
			return false;
	}
	void clear()
	{
		Node* curr = first;
		//last =NULL to the print fn
		last = NULL;
		for (int i = 0; i < size; i++)
		{
			first = first->next;
			delete curr;
			curr = first;
		}
		size = 0;
	}
	int linkedListSize()
	{
		return size;
	}
	T retrieveAt(int index)
	{
		Node* curr = first;
		for (int i = 0; i < index; i++)
		{
			curr = curr->next;
		}
		return curr->item;
	}

	void replaceAt(T element, int index)
	{
		if (index < 0 || index >= size)
		{
			cout << "out of range\n";
			return;
		}
		else
		{
			Node* curr = first;
			for (int i = 0; i < index; i++)
			{
				curr = curr->next;
			}
			curr->item = element;
		}
	}

	bool isExist(T element)
	{
		Node* curr = first;
		while (curr != NULL)
		{
			if (curr->item == element)
				return true;
			curr = curr->next;
		}
		return false;
	}

	bool isItemAtEqual(T element, int index)
	{
		if (index < 0 || index >= size)
		{
			cout << "out of range\n";
			return false;
		}
		else
		{
			Node* curr = first;
			for (int i = 0; i < index; i++)
			{
				curr = curr->next;
			}
			if (curr->item == element)
				return true;
			else
				return false;
		}
	}

	void swap(int firstItemIndex, int secondItemIndex)
	{
		if (firstItemIndex < 0 || firstItemIndex >= size || secondItemIndex < 0 || secondItemIndex >= size)
		{
			cout << "Out of range\n";
			return;
		}

		if (firstItemIndex > secondItemIndex)
		{
			int temp = firstItemIndex;
			firstItemIndex = secondItemIndex;
			secondItemIndex = temp;
		}
		else if (firstItemIndex == secondItemIndex)
			return;

		else
		{
			Node* beforeFirst = NULL;
			Node* firstIndex = first;
			for (int i = 0; i < firstItemIndex; i++)
			{
				beforeFirst = firstIndex;
				firstIndex = firstIndex->next;
			}
			Node* afterFirst = firstIndex->next;



			Node* beforeSecond = NULL;
			Node* secondIndex = first;
			for (int i = 0; i < secondItemIndex; i++)
			{
				beforeSecond = secondIndex;
				secondIndex = secondIndex->next;
			}
			Node* afterSecond = secondIndex->next;

			if (beforeFirst == NULL)
			{ 
				first = secondIndex;
				secondIndex->prev = NULL;
			}
			else
			{
				beforeFirst->next = secondIndex;
			}
			secondIndex->prev = beforeFirst;
			
			beforeSecond->next = firstIndex;
			firstIndex->prev = beforeSecond;

			firstIndex->next = afterSecond;
			secondIndex->next = afterFirst;

			if (afterSecond) {
				afterSecond->prev = firstIndex;
			}


			if (secondIndex->next) {
				secondIndex->next->prev = secondIndex;
			}


		}
	}
};

int main()
{
	Doule_Linked_List <int> dl;
	dl.insertAtHead(10);
	dl.insertAtTail(20);
	dl.insertAtTail(30);
	dl.insertAtTail(40);
	dl.insertAtHead(0);
	dl.insertAt(1, 1);
	dl.print();
	
	dl.swap(0, 5);
	dl.print();
}

