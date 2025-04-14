// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <utility>
#include<stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

template <class T>
class Single_Linked_List 
{
private:
	struct Node 
	{
		T item;
		Node* next;
	};
	Node* first;
	Node* last;
	int size ;
public:
	Single_Linked_List()
	{
		first = last = NULL;
		size = 0;
	}
	bool is_impty()
	{
		if (first == NULL)
			return true;
		else
			return false;
	}
	void insertAtHead(T element)
	{
		Node* newnode = new Node;
		newnode->item=element;		
		if (first == NULL)
		{
			first = last = newnode;
			newnode->next = NULL;

		}
		else
		{
			newnode->next = first;
			first = newnode;
		}
		size++;
	}
	void insertAtTail(T element)
	{
		Node *newNode = new Node;
		newNode->item = element;
		if (first==NULL)
		{
			first = last = newNode;
			newNode->next = NULL;
		}
		else
		{
			last->next = newNode;
			newNode->next = NULL;
			last = newNode;
		}
		size++;
	}
	void insertAt(T element, int index)
	{
		
		if (index == 0)
			insertAtHead(element);

		else if (index == size )
			insertAtTail(element);

		else if (index > size  || index < 0)
			cout << "Out of range"<<endl;

		else
		{
			Node* newNode = new Node;
			newNode->item = element;
			//curr will point at the index-1 
			Node* curr = first;
			for (int i = 1; i < index; i++)
			{
				curr = curr->next;
			}
			newNode->next = curr->next;
			curr->next = newNode;
			size++;
		}

	}
	void print()
	{
		Node* P = first;
		while (P != NULL)
		{
			cout << P->item<<" ";
			P = P->next;

		}
		cout << endl;
	
	}
	void removeAtHead()
	{
		Node* curr = first;
		first = first->next;
		delete curr;
		size--;
	}
	void removeAtTAil()
	{
		if (size == 1)
		removeAtHead();

		else
		{
			Node* curr = first;
			while (curr->next != last)
			{
				curr = curr->next;
			}
			delete last;
			last = curr;
			last->next = NULL;
			size--;
		}
	}
	void removeAt(int index)
	{
		if (index >= size || index < 0)
		{
			cout << "can't remvoe because it is out of range"<<endl;
			return ;
		}
		
		else if (size == 1)
			removeAtHead();
		else
		{
			Node* curr = first->next, * prev = first;
			
			for (int i = 1; i <index ; i++)
			{
				curr = curr->next;
				prev = prev->next;
			}
			prev->next = curr->next;
			delete curr;
			size--;
		}
			
	}
	void clear()
	{
		Node* curr = first;
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
		if (index >= size || index < 0)
		{
			cout << "Out of range\n";
			return 0;
		}
		else
		{
			Node* curr = first;
			for (int i = 0; i < index; i++)
			{
				curr = curr->next;
			}
			return curr->item;
		}
	}
	void replaceAt(T element , int index)
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
		while(curr!=NULL)
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
		if (firstItemIndex>secondItemIndex)
		{
			int temp = firstItemIndex;
			firstItemIndex = secondItemIndex;
			secondItemIndex = temp;
		}
		if (firstItemIndex < 0 || firstItemIndex >= size || secondItemIndex < 0 || secondItemIndex >= size)
		{
			cout << "Out of range\n";
			return;
		}
		else if (firstItemIndex == secondItemIndex)
			return;

		else
		{
			Node* beforeFirst=NULL;
			Node* firstIndex = first;
			for (int i = 0; i < firstItemIndex; i++)
			{
				beforeFirst = firstIndex;
				firstIndex = firstIndex->next;
			}
			

			Node* beforeSecond = NULL;
			Node* secondIndex = first;

			for (int i = 0; i < secondItemIndex; i++)
			{
				beforeSecond = secondIndex;
				secondIndex = secondIndex->next;
			}
			Node* afterSecond = secondIndex->next;
			
			if (beforeFirst == NULL)
				first = secondIndex;
			else
			beforeFirst->next = secondIndex;
			


			beforeSecond->next = firstIndex;
			secondIndex->next = firstIndex->next;
			firstIndex->next = afterSecond;

		}
	}
};

int main()
{
	Single_Linked_List <char> l;
	l.insertAtHead('a');
	l.insertAtTail('b');
	l.insertAtTail('d');
	l.insertAtTail('e');
	l.insertAt('c',2);
	l.insertAtTail('f');
	l.insertAtTail('j');
	l.print();
	l.swap(0,4);
	l.print();
}

