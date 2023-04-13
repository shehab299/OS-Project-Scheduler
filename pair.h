#include<iostream>
using namespace std;
template <class t>
class pair
{
	t first;
	t second;
public:
	pair();
	pair (t f,t s);
	pair(const pair<t>& p);
	void set_first(const t &f);
	void set_second(const t &s);
	t get_first()const;
	t get_second()const;
	void Display()const;
};
template <class t>
pair<t>::pair()
{
}
template <class t>
pair<t>::pair(t f,t s)
{
	set_first(f);
	set_second(s);
}
template <class t>
pair<t>::pair(const pair<t>& p)//copy construcor
{
	first=p.first;
	second=p.second;
}
template <class t>
void pair<t>:: set_first(const t &f)
{
	first=f;
}
template <class t>
void pair<t>:: set_second(const t &s)
{
	second =s;
}
template <class t>
t pair<t>:: get_first()const
{
	return first;
}
template <class t>
t pair<t>:: get_second()const
{
	return second;
}
template <class t>
void pair<t>::Display()const
{
	cout<<"("<<fisrt<<","<<second<<")"<<endl;
}