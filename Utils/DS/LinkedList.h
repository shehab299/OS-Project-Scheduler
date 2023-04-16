#pragma once

#include "Node.h"
#include"../../Entities/Process.h"
#include <iostream>
using std::cout;
using std::endl;
template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
public:
	LinkedList();
	LinkedList(const LinkedList<T>& LL);
	void printList() const;
	int getSize();
	bool isEmpty();
	Node<T>* getHead();
	void setHead(Node<T>* ptr);
	void insertBeg(const T& data);
	void insertEnd(const T& data);
	void deleteFirst();
	void deleteLast();
	void deleteAll();
	bool deleteNode(T& value);
	Node<T>* getPointerTo(const T& target) const;
	~LinkedList();

};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: LinkedList()
The constructor of the LinkedList class.

*/
template <typename T>
LinkedList<T>::LinkedList()
{
	Head = nullptr;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: LinkedList(const LinkedList<T>& LL)
The copy constructor of the LinkedList class.

*/

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& LL)
{
	Node<T>* origChainPtr = LL->Head;
	if (!origChainPtr)
		Head = nullptr; // Original LinkedList is empty; so is copy
	else
	{
		// Copy first node
		Head = new Node<T>();
		Head->setItem(origChainPtr->getItem()); // Copy remaining nodes
		Node<T>* newChainPtr = Head;  // Last-node pointer
		while (origChainPtr)
		{
			origChainPtr = origChainPtr->getNext();// Advance pointer
			// Get next item from original chain 
			T nextItem = origChainPtr->getItem();
			// Create a new node containing the next item
			Node<T>* newNodePtr = new Node<T>(nextItem);



			// Link new node to end of new chain   
			newChainPtr->setNext(newNodePtr);
			// Advance pointer to new last node          
			newChainPtr = newChainPtr->getNext();
		}   // end while   

		newChainPtr->setNext(nullptr); // Flag end of new chain    
	}   // end if
} // end copy constructor 
////////////////////////////////////////////////////////////////////////
/*
* Function: PrintList.
* prints the values of all nodes in a linked list.
*/
template <typename T>
void LinkedList<T>::printList()	const
{
	cout << "\nprinting list contents:\n\n";
	Node<T>* p = Head;

	while (p)
	{
		cout << "[ " << p->getItem() << " ]";
		cout << "--->";
		p = p->getNext();
	}
	cout << "NULL\n";
}
////////////////////////////////////////////////////////////////////////
/*
* Function: insertBeg.
* Creates a new node and adds it to the beginning of a linked list.
*
* Parameters:
*	- data : The value to be stored in the new node.
*/

template<typename T>
void LinkedList<T>::setHead(Node<T>* ptr)
{
	Head = ptr;
}

template <typename T>
void LinkedList<T>::insertBeg(const T& data)
{
	Node<T>* R = new Node<T>(data);
	R->setNext(Head);
	Head = R;

}
////////////////////////////////////////////////////////////////////////
/*
* Function: insertEnd.
* Creates a new node and adds it to the End of a linked list.
*
* Parameters:
*	- data : The value to be stored in the new node.
*/
template <typename T>
void LinkedList<T>::insertEnd(const T& data)
{
	Node<T>* ptr = new Node<T>;
	ptr->setItem(data);
	ptr->setNext(NULL);
	Node<T>* temp = Head;
	if (temp)
	{
		while (temp->getNext())
		{
			temp = temp->getNext();
		}
		temp->setNext(ptr);
		return;
	}
	else
		Head = ptr;
}
////////////////////////////////////////////////////////////////////////
/*
* Function: deleteAll.
* Deletes all nodes of the list.
*/
template <typename T>
void LinkedList<T>::deleteAll()
{
	Node<T>* P = Head;
	while (Head)
	{
		P = Head->getNext();
		delete Head;
		Head = P;
	}
}
////////////////////////////////////////////////////////////////////////
/*
* Function: getSize.
*returns the size of the linkedlist.
*/
template <typename T>
int LinkedList<T>::getSize()
{
	int size = 0;
	Node <T>* temp = Head;
	while (temp)
	{
		size++;
		temp = temp->getNext();
	}
	return size;
}
template<typename T>
bool LinkedList<T>::isEmpty()
{
	return (Head == nullptr);
}
template<typename T>
Node<T>* LinkedList<T>::getHead()
{
	return Head;
}
////////////////////////////////////////////////////////////////////////
/*
* Function: deleteFirst.
*Deletes the first Node of the LinkedList.
*/
template <typename T>
void LinkedList<T> ::deleteFirst()
{
	Node<T>* CurPtr = Head->getNext();
	delete Head;
	Head = CurPtr;
}
////////////////////////////////////////////////////////////////////////
/*
* Function: DeleteLast.
*Deletes the last Node of the LinkedList.
*/
template <typename T>
void LinkedList<T> ::deleteLast()
{
	Node<T>* CurPtr = Head;
	while (CurPtr->getNext()->getNext())
	{
		CurPtr = CurPtr->getNext();
	}
	CurPtr->DeleteNext();
}
////////////////////////////////////////////////////////////////////////
/*
* Function: deleteNode.
*deletes the first node with the given value (if found) and returns true
*if not found, returns false.
*/
template<typename T>
bool LinkedList<T>::deleteNode(T& value)
{
	Node<T>* key1, * key2;
	key1 = Head;
	key2 = key1->getNext();
	if (Head->getItem() == value)
	{
		Head = Head->getNext();
		delete key1;
		return true;
	}
	while (key2)
	{
		if (key2->getItem() == value)
		{
			key1->setNext(key2->getNext());
			delete key2;
			return true;
		}
		key1 = key1->getNext();
		key2 = key2->getNext();
	}
	return false;
}

template <typename T>
Node<T>* LinkedList<T>::getPointerTo(const T& target) const
{

	bool found = false;
	Node<T>* curPtr = Head;
	while (!found && (curPtr != nullptr))
	{
		if (target == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	}   // end while 
	return curPtr;
} // end getPointerTo The definition 
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the LinkedList
*/
template <typename T>
LinkedList<T>:: ~LinkedList()
{
	deleteAll();
}



