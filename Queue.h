#include "Node.h"
using namespace std;


template <typename T>
class Queue
{
private:
	Node <T>* backPtr;
	Node <T>* frontPtr;
public:
	Queue();
	int queueSize();
	bool isEmpty()	const;
	bool enqueue(const T& newEntry);
	bool dequeue();
	T peek()  const;
	void printQueue();
	~Queue();

	//copy constructor
	Queue(const Queue <T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: QueueSize
To return the size of the queue,

Input: none
Output: size of the queue
*/

template <typename T>
int Queue<T>::queueSize()
{
	int size = 0;
	Queue<T> temp;
	while (!isEmpty())
	{
		temp.enqueue(frontPtr->getItem());
		dequeue();
		size++;

	}
	while (!temp.isEmpty())
	{
		enqueue(temp.peek());
		temp.dequeue();
	}
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
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool Queue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
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
void Queue <T>::printQueue()
{
	Queue <T> temp;
	cout << "\nQueue contents: ";
	while (!isEmpty())
	{
		cout << frontPtr->getItem() << " ";
		temp.enqueue(frontPtr->getItem());
		dequeue();

	}
	while (!temp.isEmpty())
	{
		enqueue(temp.peek());
		temp.dequeue();
	}
	cout << endl;
}
