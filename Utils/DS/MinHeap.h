#pragma once

#include<iostream>



using namespace std;

template<typename T , bool pointer>
class MinHeap
{
private:
	T* minHeap;
	int capacity;
	int count;

	void swap(T& el1, T& el2);
	int parentIndex(int in);
	int leftIndex(int in);
	int rightIndex(int in);


public:
	MinHeap(int maxCapacity = 150);
	MinHeap(const MinHeap<T,pointer>& temp);
	int getCount();
	bool isEmpty();
	void resize();
	void minHeapify(int key);
	void insert(T val);
	void deleteMin();
	std::string toString() const;
	T minElement() const;
};

template<class T, bool pointer>
MinHeap<T,pointer>::MinHeap(int maxCapacity)
{
	capacity = (maxCapacity >= 1) ? maxCapacity : 1;
	minHeap = new T[maxCapacity];
	count = 0;
}

template<class T, bool pointer>
void MinHeap<T,pointer>::swap(T& el1, T& el2)
{
	T temp = el1;
	el1 = el2;
	el2 = temp;
}

template<class T, bool pointer>
int MinHeap<T,pointer>::parentIndex(int in)
{
	return ((in - 1) / 2);
}


template<class T, bool pointer>
int MinHeap<T,pointer>::leftIndex(int in)
{
	return (2 * in + 1);

}
template<class T, bool pointer>
int MinHeap<T,pointer>::rightIndex(int in)
{
	return (2 * in + 2);
}

template<class T, bool pointer>
T MinHeap<T,pointer>::minElement() const
{
	return minHeap[0];
}


template<class T, bool pointer>
void MinHeap<T,pointer>::insert(T k)
{
	if (count >= capacity)
		resize();

	int in = count;
	minHeap[count++] = k;

	if (!pointer)
	{
		while (in != 0 && minHeap[parentIndex(in)] > minHeap[in])
		{
			swap(minHeap[parentIndex(in)], minHeap[in]);
			in = parentIndex(in);
		}
	}

	else if (pointer)
	{
		while (in != 0 && *minHeap[parentIndex(in)] > *minHeap[in])
		{
			swap(minHeap[parentIndex(in)], minHeap[in]);
			in = parentIndex(in);
		}
	}
}


template<class T, bool pointer>
void MinHeap<T,pointer>::minHeapify(int key)
{
	if (key >= count)
		return;

	int lef = leftIndex(key);
	int rig = rightIndex(key);
	int smallest = key;
	
	if (!pointer) 
	{
		if (lef < count && minHeap[lef] < minHeap[smallest])
			smallest = lef;
		if (rig < count && minHeap[rig] < minHeap[smallest])
			smallest = rig;
	}
	else if (pointer)
	{
		if (lef < count && *minHeap[lef] < *minHeap[smallest])
			smallest = lef;
		if (rig < count && *minHeap[rig] < *minHeap[smallest])
			smallest = rig;
	}


	if (smallest != key)
	{
		swap(minHeap[key], minHeap[smallest]);
	}
}


template<class T, bool pointer>
void MinHeap<T,pointer>::deleteMin()
{
	minHeap[0] = minHeap[count - 1];
	minHeapify(0);
	count--;
}

template<class T, bool pointer>
std::string MinHeap<T,pointer>::toString() const
{
	return "";
}


template<class T, bool pointer>
bool MinHeap<T,pointer>::isEmpty()
{
 	return (count == 0);
}


template<class T, bool pointer>
MinHeap<T,pointer>::MinHeap(const MinHeap<T,pointer>& m)
{
	minHeap = new T[m.capacity];
	for (int i = 0; i < m.count; i++)
		minHeap[i] = m.minHeap[i];
}


template<class T , bool pointer>
void MinHeap<T,pointer>::resize()
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




template<typename T, bool pointer>
int MinHeap<T,pointer>::getCount()
{
	return count;
}



