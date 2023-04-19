#pragma once
#include<iostream>
using namespace std;

template<typename T>
class MinHeap
{
private:
	T* minHeap;
	int capacity;
	int count;
	void swap(T& el1, T& el2);

public:
	MinHeap(int maxCapacity = 150);
	MinHeap(const MinHeap<T>& temp);
	void setCapacity(int c);
	void setCount(int c);
	int getCount();
	bool isEmpty();
	void resize();
	void minHeapify(int key);
	void insert(T val);
	int parentIndex(int in);
	int leftIndex(int in);
	int rightIndex(int in);
	void decreaseKey(int key, T val);
	T extractMin();
	void deleteMin(int in);
	std::string toString() const;
	T minElement() const;
};

template<class T>
MinHeap<T>::MinHeap(int maxCapacity)
{
	capacity = (maxCapacity >= 1) ? maxCapacity : 1;
	minHeap = new T[maxCapacity];
	count = 0;
}

template<class T>
void MinHeap<T>::swap(T& el1, T& el2)
{
	T temp = el1;
	el1 = el2;
	el2 = temp;
}

template<class T>
int MinHeap<T>::parentIndex(int in)
{
	return ((in - 1) / 2);
}


template<class T>
int MinHeap<T>::leftIndex(int in)
{
	return (2 * in + 1);

}
template<class T>
int MinHeap<T>::rightIndex(int in)
{
	return (2 * in + 2);
}

template<class T>
T MinHeap<T>::minElement()const
{
	return minHeap[0];
}

template<class T>
void MinHeap<T>::insert(T k)
{
	if (count >= capacity)
		resize();

	int in = count;
	minHeap[count++] = k;
	while (in != 0 && minHeap[parentIndex(in)] > minHeap[in])
	{
		swap(minHeap[parentIndex(in)], minHeap[in]);
		in = parentIndex(in);
	}
}


template<class T>
void MinHeap<T>::minHeapify(int key)
{
	if (key >= capacity)
		return;
	int lef = leftIndex(key);
	int rig = rightIndex(key);
	int smallest = key;
	
	if (lef < capacity && minHeap[lef] < minHeap[smallest])
		smallest = lef;
	if (rig < capacity && minHeap[rig] < minHeap[smallest])
		smallest = rig;
	if (smallest != key)
	{
		swap(minHeap[key], minHeap[smallest]);
	}
}


template<class T>
T MinHeap<T>::extractMin()
{
	if (count == 1)//special case
		return minHeap[0];
	else
	{
		T minelement = minElement();
		minHeap[0] = minHeap[count - 1];
		count--;
		minHeapify(0);
		return minelement;
	}
}


template<class T>
void MinHeap<T>::decreaseKey(int key, T val)
{
	minHeap[key] = val;
	while (key != 0 && minHeap[parentIndex(key)] > minHeap[key])
	{
		swap(minHeap[parentIndex(key)], minHeap[key]);
		key = parentIndex(key);
	}
}


template<class T>
void MinHeap<T>::deleteMin(int in)
{
	if (in >= capacity)
		return;
	int found = 0;
	for (int i = 0; i < count; i++)
	{
		if (i == in)
			found = i;
	}
	minHeap[found] = minHeap[count - 1];
	minHeapify(0);
	count--;
}

template<class T>
std::string MinHeap<T>::toString() const
{
	std::string text = "";
	for (int i = 0; i < count; i++) {
		text += to_string(minHeap[i]);
		if (i != count - 1)
			text += ", ";
	}
	return text;
}


template<class T>
bool MinHeap<T>::isEmpty()
{
	return (count == 0);
}

template<class T>
MinHeap<T>::MinHeap(const MinHeap<T>& m)
{
	minHeap = new T[m.capacity];
	for (int i = 0; i < m.count; i++)
		minHeap[i] = m.minHeap[i];
}

template<class T>
void MinHeap<T>::resize()
{
	T* arr = new T[capacity * 2];
	for (int i = 0; i < count; i++)
	{
		arr[i] = minHeap[i];
	}
	delete minHeap;
	minHeap = arr;
	capacity = capacity * 2;
}


template<class T>
void MinHeap<T>::setCapacity(int c)
{
	capacity = (c > 0) ? c : capacity;
}


template<class T>
void MinHeap<T>::setCount(int c)
{
	count = (c >= 0) ? c : 0;
}

template<typename T>
int MinHeap<T>::getCount()
{
	return count;
}







