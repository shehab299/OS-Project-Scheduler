#pragma once
#include<iostream>
using namespace std;
#include"Node.h"
template<class T>
class CircularQueue
{
	Node<T>* front;
	Node<T>* rear;
public:
	CircularQueue();
	bool isEmpty();
	bool enqueue(const T& item);
	bool dequeue();
	T peek();
	void displayQueue();
	void rotate();
	CircularQueue(const CircularQueue<T>& CQ);

};
template <class T>
CircularQueue<T>::CircularQueue()
{
	front = rear = NULL;
}
template <class T>
bool CircularQueue<T>::isEmpty()
{
	return (!front && !rear);
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
template <class T>
void CircularQueue<T>::displayQueue()
{
	if (isEmpty())
		return;
	else
	{
		Node<T>* cur = front;
		while (cur && cur != rear)
		{
			cout << cur->getItem() << " ";
			cur = cur->getNext();
		}
		cout << rear->getItem();
		cout << endl;

	}
}
template<class T>
CircularQueue<T>::CircularQueue(const CircularQueue<T>& CQ)
{
	Node<T>* frontptr = CQ.front;
	if (!frontptr) //CQ is empty
	{
		front = rear = NULL;
	}

	//insert the first node
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
		T val, val2;
		val=peek();
		dequeue();
		while (peek(val2))
		{
			temp.enqueue(val2);
			dequeue();
		}
		temp.enqueue(val);
		while (temp.peek(val2))
		{
			enqueue(val2);
			temp.dequeue();
		}

	}
}


