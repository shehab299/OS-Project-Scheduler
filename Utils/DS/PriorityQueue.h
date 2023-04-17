#pragma once

#include"MinHeap.h"

template <typename T>
class PriorityQueue
{
private:
	MinHeap<T>m;
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue<T>& pq);
	void enqueue(const T & val);
	void dequeue();
	T peek();
	bool isEmpty();
	void displayQueue();
};

template<class T>
PriorityQueue<T>::PriorityQueue()
{
	m.setCapacity(150);
	m.setCount(0);
}


template <class T>
void PriorityQueue<T>::enqueue(const T & val)
{
	m.insert(val);
}

template<class T>
T PriorityQueue<T>::peek()
{
	T top = m.minElement();
	return top;
}


template <class T>
bool PriorityQueue<T>::isEmpty()
{
	return m.isEmpty();
}

template<class T>
void PriorityQueue<T>::dequeue()
{
	m.deleteMin(0);
}

template<class T>
void PriorityQueue<T>::displayQueue()
{
	m.display();
}

template<class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& pq)
{
	m = pq.m;
}

