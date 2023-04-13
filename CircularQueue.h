#include<iostream>
using namespace std;
#include"Node.h"
template<class t>
class CircularQueue
{
	Node<t>* front;
	Node<t>* rear;
public:
	CircularQueue();
	bool IsEmpty();
	bool enqueue(const t & item);
	bool dequeue();
	bool peek( t & item);
	void DisplayQueue();
	void Rotate();
	CircularQueue(const CircularQueue<t> & CQ);

};
template <class t>
CircularQueue<t>::CircularQueue()
{
	front=rear=NULL;
}
template <class t>
bool CircularQueue<t>::IsEmpty()
{
	return (!front&&!rear);
}
template <class t>
bool CircularQueue<t>::enqueue(const t & item)
{
	Node<t>* newnode=new Node<t>(item);
	if(!newnode)                    // cheak overflow
		return false;
	if(IsEmpty())                   //insertlast
		front=rear=newnode;
	else
	{
		rear->set_next(newnode);
		rear=rear->get_next();		
	}
	rear->set_next(front);           // CircularQueue proprty
	return true;
}
template <class t>
bool CircularQueue<t>::dequeue()
{
	if(IsEmpty())                    //cheack underflow
		return false;
	else if(front==rear)             //cheak single node
	{
		delete front;
		front =rear=NULL;
	}
	else
	{
		Node<t>* cur=front;
		front=front->get_next();
		delete cur;
		rear->set_next(front);
	}
	return true;
}
template <class t>
bool CircularQueue<t>::peek( t & item)
{
	if(IsEmpty())
		return false;
	else
	{
		item=front->get_data();
		return true;
	}
}
template <class t>
void CircularQueue<t>::DisplayQueue()
{
	if(IsEmpty())
		return ;
	else
	{
		Node<t>*cur=front;
		while(cur&&cur!=rear)
		{
			cout<<cur->get_data()<<" ";
			cur=cur->get_next();
		}
		cout<<rear->get_data();
		cout<<endl;

	}
}
template<class t>
CircularQueue<t>::CircularQueue(const CircularQueue<t> & CQ)
{
	Node<t>* frontptr = CQ.front;
	if (!frontptr) //CQ is empty
	{
		front = rear = NULL;		
	}

	//insert the first node
	Node<t>* ptr = new Node<t>(frontptr->get_data());
	if(ptr)
	{
		front = rear = ptr;
		frontptr = frontptr->get_next();
		//insert remaining nodes
		while (frontptr)
		{
			Node<t>* ptr = new Node<t>(frontptr->get_data());
			rear->set_next(ptr);
			rear = ptr;
			frontptr = frontptr->get_next();
		}
		rear->set_next(front);
	}
}
template<class t>
void CircularQueue<t>::Rotate()
{
	if(IsEmpty())
		return;
	else if(front==rear)
		return;
	else
	{
		CircularQueue<t>temp;
		t val,val2;
		peek(val);
		dequeue();
		while(peek(val2))
		{
			temp.enqueue(val2);
			dequeue();
		}
		temp.enqueue(val);
		while(temp.peek(val2))
		{
			enqueue(val2);
			temp.dequeue();
		}

	}
}