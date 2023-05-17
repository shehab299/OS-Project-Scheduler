#pragma once


#include "Node.h"
#include <iostream>

using std::cout;
using std::endl;

template <typename T>
class Queue
{
private:
	Node <T>* frontPtr;
	Node <T>* backPtr;
	int size;
public:
	Queue();
	Queue(const Queue <T>& LQ);
	std::string toString();
	std::string toString2();
	bool enqueue(T newEntry);
	bool dequeue();
	T peek()  const;
	int getSize();
	bool isEmpty()	const;
	~Queue();
};


/*
Function: Queue()
The constructor of the Queue class.
*/

template <typename T>
Queue<T>::Queue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}

/*
Function: QueueSize
To return the size of the queue,

Input: none
Output: size of the queue
*/

template <typename T>
int Queue<T>::getSize()
{
	return size;
}

/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/

template <typename T>
bool Queue<T>::isEmpty() const
{
	return (size == 0);
}


/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Queue<T>::enqueue(T newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);

	if (!newNodePtr)
		return false;

	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is the last node now
	size++;
	return true;
} // end enqueue


  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*Function: dequeue
  Removes the front of this queue. That is, removes the item that was added
  earliest.

  Input: None.
  Output: True if the operation is successful; otherwise false.
  */

template <typename T>
bool Queue<T>::dequeue()
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	size--;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
T Queue<T>::peek() const
{
	if (isEmpty())
		throw std::out_of_range("Queue is empty");
	return frontPtr->getItem();
}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
Queue<T>::~Queue()
{
	//Free (Dequeue) all nodes in the queue
	while (dequeue());
}

/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: Queue<T>: The Queue to be copied
Output: none
*/

template <typename T>
Queue<T>::Queue(const Queue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: PrintQueue
To print the Queue,

Input: none
Output: Queue elements
*/
template <typename T>
std::string Queue <T>::toString()
{
	std::string text = "";
	Node<T>* temp = frontPtr;
	while(temp)
	{
		text += to_string(temp->getItem());
		if (temp->getNext())
			text += ", ";
		temp = temp->getNext();
	}
	return text;
}
template <typename T>
std::string Queue <T>::toString2()
{
	std::string text = "";
	Node<T>* temp = frontPtr;
	while (temp)
	{
		text += toString(temp->getItem());		
		temp = temp->getNext();
	}
	return text;
}
