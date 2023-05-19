#pragma once


#include "MinHeap.h"

template <typename T,bool pointer>
class PriorityQueue
{
private:
	MinHeap <T,pointer> m;
public:
	PriorityQueue();
	PriorityQueue(const PriorityQueue<T,pointer>& pq);
	void enqueue(const T & val);
	void dequeue();
	int getSize();
	std::string toString();
	T peek();
	bool isEmpty();
};

template<class T,bool pointer>
PriorityQueue<T, pointer>::PriorityQueue()
{
}


template<class T, bool pointer>
void PriorityQueue<T, pointer>::enqueue(const T & val)
{
	m.insert(val);
}

template<class T, bool pointer>
T PriorityQueue<T, pointer>::peek()
{
	T top = m.minElement();
	return top;
}


template<class T, bool pointer>
bool PriorityQueue<T, pointer>::isEmpty()
{
	return m.isEmpty();
}

template<class T, bool pointer>
void PriorityQueue<T, pointer>::dequeue()
{
	m.deleteMin();
}

template<class T, bool pointer>
inline int PriorityQueue<T, pointer>::getSize()
{
	return m.getCount();
}

template<class T, bool pointer>
std::string PriorityQueue<T, pointer>::toString()
{
	return m.toString();
}

template<class T, bool pointer>
PriorityQueue<T,pointer>::PriorityQueue(const PriorityQueue<T, pointer>& pq)
{
	m = pq.m;
}

