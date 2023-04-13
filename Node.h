template <class t>
class Node
{
	t data;
	Node<t>* next;
public:
	Node();
	Node(const t & item);
	Node(const t & item,Node<t>* ptr);
	void set_data(const t & item);
	void set_next( Node<t>* ptr);
	t get_data()const;
	Node<t>* get_next()const;
};
template < class t>
Node<t>::Node() 
{
	next = NULL;
} 
template < class t>
Node<t>::Node( const t & item)
{
	data = item;
	next = NULL;
} 

template < class t>
Node<t>::Node( const t & item, Node<t>* ptr)
{
	data = item;
	next = ptr;
}
template < class t>
void Node<t>::set_data( const t & item)
{
	data = item;
} 

template < class t>
void Node<t>::set_next(Node<t>* ptr)
{
	next = ptr ;
} 

template < class t>
t Node<t>::get_data() const
{
	return data;
} 

template < class t>
Node<t>* Node<t>::get_next() const
{
	return next;
} 
