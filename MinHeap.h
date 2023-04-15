#include<iostream>
using namespace std;
template<class t>
class MinHeap
{
	t * minheap;
	int capacity;
	int count;
	void swap(t & el1,t &el2 );
public:
	MinHeap(int maxs=150); 
	MinHeap(const MinHeap<t>& temp); 
	void setCapacity(int c);
	void setCount(int c);
	bool isEmpty();
	void resize();
	void minHeapify(int key);
	void insert(t val);	
	int parentIndex(int in);
	int leftIndex(int in);
	int rightIndex(int in);
	void decreaseKey(int key,t val);
	t extractMin();
	void deleteMin(int in);
	void display()const;
	t mini()const;

};
template<class t>
MinHeap<t>::MinHeap(int maxs=150)
{
	capacity=(maxs>=1)?maxs:1;
	minheap=new t[maxs];
	count=0;
}
template<class t> 
void MinHeap<t>::swap(t & el1,t &el2 )
{
	t temp = el1;
	el1 = el2;
	el2 = temp;
}
template<class t>
int MinHeap<t>::parentIndex(int in)
{
	return ((in - 1) / 2);
}
template<class t>
int MinHeap<t>::leftIndex(int in)
{
	return (2 * in + 1 );
}
template<class t>
int MinHeap<t>::rightIndex(int in)
{
	return (2 * in + 2);
}
template<class t>
t MinHeap<t>::mini()const
{
	return minheap[0];
}
template<class t>
void MinHeap<t>::insert(t k)
{
	if(count >= capacity)
		resize() ;	
	
		int in = count;
		minheap[count++] = k;
		while(in!= 0 && minheap[parentIndex(in)] > minheap[in])
		{
			swap(minheap[parentIndex(in)],minheap[in]);
			in = parentIndex(in);
		}
		
		
}
template<class t>
void MinHeap<t>::minHeapify(int key)
{
	if(key>=capacity)
		return;
	int lef = leftIndex(key);
	int rig = rightIndex(key);
	int smallest=key;
	if(lef < capacity && minheap[lef] < minheap[smallest])
		smallest=lef;	
	if(rig < capacity && minheap[rig] < minheap[smallest])
		smallest=rig;
	if(smallest != key)
	{
		swap(minheap[key],minheap[smallest]);
	}
}
template<class t>
t MinHeap<t>::extractMin()
{
	if(count==1)//special case
		return minheap[0];
	else
	{
		t minelemt = mini();
		minheap[0] = minheap[count-1];
		count--;
		minHeapify(0);
		return minelemt;
	}
	
}
template<class t>
void MinHeap<t>::decreaseKey(int key, t val)
{	
		minheap[key] = val;
		while(key != 0 && minheap[parentIndex(key)] > minheap[key])
		{
			swap(minheap[parentIndex(key)],minheap[key]);
			key = parentIndex(key);
		}
}
template<class t>
void MinHeap<t>::deleteMin(int in)
{
	if(in >= capacity)
		return;
	int found=0;
	for(int i = 0 ; i<count ; i++)
	{
		if(i == in)
			found = i;
	}
	minheap[found] = minheap[count-1];
	minHeapify(0);
	count--;
}
template<class t>
void MinHeap<t>::display()const
{
	for(int i = 0 ; i < count ; i++)
		cout<<minheap[i]<<" ";
	cout<<endl;
}
template<class t>
bool MinHeap<t>::isEmpty()
{
	return (count == 0);
}
template<class t>
MinHeap<t>::MinHeap(const MinHeap<t> & m)
{
	minheap=new t[m.capacity];
	for(int i=0;i<m.count;i++)
		minheap[i]=m.minheap[i];
}
template<class t>
void MinHeap<t>::resize()
{
	t *arr= new t[capacity*2];
	for(int i=0;i<count;i++)
	{
		arr[i]=minheap[i];
	}
	delete minheap;
	minheap=arr;	
	capacity=capacity*2;	
}
template<class t>
void MinHeap<t>::setCapacity(int c)
{
	capacity=(c>=0)?c:0;
}
template<class t>
void MinHeap<t>::setCount(int c)
{
	count=(c>=0)?c:0;
}
