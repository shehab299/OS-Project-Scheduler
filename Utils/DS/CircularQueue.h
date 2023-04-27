#pragma once
#include<iostream>
using namespace std;
#include"Node.h"
template<class T>
class CircularQueue
{
	Node<T>* front;
	Node<T>* rear;
	int size;
public:
	CircularQueue();
	bool isEmpty();
	bool enqueue(const T& item);
	bool dequeue();
	T peek();
	void display();
	std::string toString();
	int getSize();
	void rotate();
	CircularQueue(const CircularQueue<T>& CQ);

};
template <class T>
CircularQueue<T>::CircularQueue() : size(0) , front(nullptr) , rear(nullptr)
{
}

template <class T>
bool CircularQueue<T>::isEmpty()
{
	return size == 0;
}
template <class T>
bool CircularQueue<T>::enqueue(const T& item)
{
	Node<T>* newnode = new Node<T>(item);
	if (!newnode)                    // cheak overflow
		return false;
	if (isEmpty())                   //insertlast
		front = rear = newnode;
	else
	{

		rear->setNext(newnode);
		rear = rear->getNext();
	}
	rear->setNext(front);           // CircularQueue proprty
	size++;
	return true;
}

template <class T>
bool CircularQueue<T>::dequeue()
{
	if (isEmpty())                    //cheack underflow
		return false;
	else if (front == rear)             //cheak single node
	{
		delete front;
		front = rear = NULL;
	}
	else
	{
		Node<T>* cur = front;
		front = front->getNext();
		delete cur;
		rear->setNext(front);
	}
	size--;
	return true;
}

template <class T>
T CircularQueue<T>::peek()
{
	if (isEmpty())
		throw std::out_of_range("Queue is empty");
	else
	{
		return front->getItem();
	}
}

template<class T>
inline void CircularQueue<T>::display()
{
}


template<class T>
std::string CircularQueue<T>::toString()
{
	string text = "";

	Node<T>* cur = front;
	while (cur != rear)
	{
		text += to_string(cur->getItem());
		if(cur != rear)
			text += ", ";
		cur = cur->getNext();
	}

	return text;
}

template<class T>
int CircularQueue<T>::getSize()
{
	return size;
}


template<class T>
CircularQueue<T>::CircularQueue(const CircularQueue<T>& CQ)
{
	Node<T>* frontptr = CQ.front;
	if (!frontptr) //CQ is empty
	{
		front = rear = NULL;
	}
	else
	{
		Node<T>* ptr = new Node<T>(frontptr->getItem());
		if (ptr)
		{
			front = rear = ptr;
			frontptr = frontptr->getNext();
			//insert remaining nodes
			while (frontptr)
			{
				Node<T>* ptr = new Node<T>(frontptr->getItem());
				rear->setNext(ptr);
				rear = ptr;
				frontptr = frontptr->getNext();
			}
			rear->setNext(front);
		}
	}
}


template<class T>
void CircularQueue<T>::rotate()
{
	if (isEmpty())
		return;
	else if (front == rear)
		return;
	else
	{
		CircularQueue<T>temp;
		T val = peek();
		dequeue();
		T val2, val3;
		while (!isEmpty())
		{
			val2 = peek();
			temp.enqueue(val2);
			dequeue();
		}
		temp.enqueue(val);
		while (!temp.isEmpty())
		{
			val3 = temp.peek();
			enqueue(val3);
			temp.dequeue();
		}

	}
}