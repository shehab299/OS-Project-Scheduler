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
	MinHeap(int maxs); 
	void minheapify(int key);
	void insert(t val);	
	int parent_index(int in);
	int left_index(int in);
	int right_index(int in);
	void decrease_key(int key,t val);
	t extract_min();
	void deletemin(int in);
	void Display()const;
	t peek()const;

};
template<class t>
MinHeap<t>::MinHeap(int maxs)
{
	capacity=(maxs>=1)?maxs:1;
	minheap=new t[maxs];
	count=0;
}
template<class t> 
void MinHeap<t>::swap(t & el1,t &el2 )
{
	t temp=el1;
	el1=el2;
	el2=temp;
}
template<class t>
int MinHeap<t>::parent_index(int in)
{
	return ((in-1)/2);
}
template<class t>
int MinHeap<t>::left_index(int in)
{
	return (2*in+1);
}
template<class t>
int MinHeap<t>::right_index(int in)
{
	return (2*in+2);
}
template<class t>
t MinHeap<t>::peek()const
{
	return minheap[0];
}
template<class t>
void MinHeap<t>::insert(t k)
{
	if(count>=capacity)
		return ;	
	else
	{
		int in =count;
		minheap[count++]=k;
		while(in!=0&&minheap[parent_index(in)]>minheap[in])
		{
			swap(minheap[parent_index(in)],minheap[in]);
			in=parent_index(in);
		}
		
	}	
}
template<class t>
void MinHeap<t>::minheapify(int key)
{
	if(key>=capacity)
		return;
	int lef=left_index(key);
	int rig=right_index(key);
	int smallest=key;
	if(lef<capacity&& minheap[lef]<minheap[smallest])
		smallest=lef;	
	if(rig<capacity&& minheap[rig]<minheap[smallest])
		smallest=rig;
	if(smallest!=key)
	{
		swap(minheap[key],minheap[smallest]);
	}
}
template<class t>
t MinHeap<t>::extract_min()
{
	if(count==1)//special case
		return minheap[0];
	else
	{
		t minelemt=peek();
		minheap[0]=minheap[count-1];
		count--;
		minheapify(0);
		return minelemt;
	}
	
}
template<class t>
void MinHeap<t>::decrease_key(int key, t val)
{	
		minheap[key]=val;
		while(key!=0&& minheap[parent_index(key)]>minheap[key])
		{
			swap(minheap[parent_index(key)],minheap[key]);
			key=parent_index(key);
		}
}
template<class t>
void MinHeap<t>::deletemin(int in)
{
	if(in>=capacity)
		return;
	int found=0;
	for(int i=0;i<count;i++)
	{
		if(i==in)
			found=i;
	}
	minheap[found]=minheap[count-1];
	minheapify(0);
	count--;
}
template<class t>
void MinHeap<t>::Display()const
{
	for(int i=0;i<count;i++)
		cout<<minheap[i]<<" ";
	cout<<endl;
}
