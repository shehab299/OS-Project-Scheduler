#include"MinHeap.h"
#include<iostream>
using namespace std;
template <class t>
class piorityQueue
{
	MinHeap<t>m;
public:
	piorityQueue();
	piorityQueue(const piorityQueue<t>&pq);
	void enqueue(t val);
	void dequeue();
	t peek();
	bool isEmpty();
	void displayQueue();

};
template<class t>
piorityQueue<t>::piorityQueue()
{
	m.setCapacity(150);
	m.setCount(0);
}
template <class t>
void piorityQueue<t>::enqueue(t val)
{
	m.insert(val);
}
template<class t>
t piorityQueue<t>::peek()
{
	t top = m.mini();
	return top;
}
template <class t>
bool piorityQueue<t>::isEmpty()
{
	return (m.isEmpty());
}
template<class t>
void piorityQueue<t>::dequeue()
{
	m.deleteMin(0);	
}
template<class t>
void piorityQueue<t>::displayQueue()
{
	m.display();	
}
template<class t>
piorityQueue<t>::piorityQueue(const piorityQueue<t> & pq)
{
	m=pq.m;
}



