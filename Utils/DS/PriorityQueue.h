#pragma once

#include"MinHeap.h"

template <typename T>
class PiorityQueue
{
private:
	MinHeap<T>m;
public:
	PiorityQueue();
	PiorityQueue(const PiorityQueue<T>& pq);
	void enqueue(const T & val);
	void dequeue();
	T peek();
	bool isEmpty();
	void displayQueue();
};

template<class T>
PiorityQueue<T>::PiorityQueue()
{
	m.setCapacity(150);
	m.setCount(0);
}


template <class T>
void PiorityQueue<T>::enqueue(const T & val)
{
	m.insert(val);
}

template<class T>
T PiorityQueue<T>::peek()
{
	T top = m.minElement();
	return top;
}


template <class T>
bool PiorityQueue<T>::isEmpty()
{
	return m.isEmpty();
}

template<class T>
void PiorityQueue<T>::dequeue()
{
	m.deleteMin(0);
}

template<class T>
void PiorityQueue<T>::displayQueue()
{
	m.display();
}

template<class T>
PiorityQueue<T>::PiorityQueue(const PiorityQueue<T>& pq)
{
	m = pq.m;
}

