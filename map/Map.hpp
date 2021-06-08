#pragma once
#include <memory>
#include "Iterator.hpp"

namespace ft {


//LESS
template< class T >
struct less {
	bool operator()( const T& lhs, const T& rhs ) const {
		return lhs < rhs;
	}
};

//PAIR
template<class T1, class T2> 
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	first_type first;
	second_type second;
	pair() : first(T1()), second(T2()) {}
	pair( const T1& x, const T2& y ) : first(x), second(y){}
	template< class U1, class U2 >
	pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {}
	pair& operator=( const pair& other ) {
		first = other.first;
		second = other.second;
		return *this;
	}
	pair<T1,T2> make_pair( T1 t, T2 u ) {
		first = t;
		second = u;
		return *this;
	}
	friend bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
		return lhs.first == rhs.first;
	}
	friend bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
		return lhs.first != rhs.first;
	}

	friend bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
		return lhs.first < rhs.first; 
	}

	friend bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
		return lhs.first > rhs.first; 
	}

	friend bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
		return lhs.first <= rhs.first; 
	}

	friend bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
		return lhs.first >= rhs.first; 
	}
};


//AVL_TREE
template<typename T>
class avl_tree {
public:
	struct node
	{
		T key;
		unsigned char height;
		node* left;
		node* right;
		node* parent;
		node() : key(T()) {left = right = 0; height = 1; parent = 0;}
		node(T k) : key(k) {left = right = 0; height = 1; parent = 0;}
		node(const node& copy) : key(copy.key), height(copy.height), left(copy.left), right(copy.right), parent(copy.parent) {}
	};
private:
	node *root;
	node *end;
public:
	avl_tree() : root(new node), end(root){}
	unsigned char get_height(node* p) {
		return p ? p->height : 0;
	}
	node *get_end() {
		return end;
	}
private:
	void take_phantom(node *p) {
		if (p->right)
			take_phantom(p->right);
		else {
			p->parent->right = 0;
			end = NULL;
			delete p;
		}
	}

	void take_phantom() {
		if (!root->left && !root->right) {
			delete root;
			root = NULL;
			end = NULL;
			return ;
		}
		if (root->right)
			take_phantom(root->right);
	}

	void push_phantom(node *p) {
		if (p->right)
			push_phantom(p->right);
		else {
			p->right = new node;
			p->right->parent = p;
			end = p->right;
		}
	}

	void push_phantom() {
		if (root->right)
			push_phantom(root->right);
		else {
			root->right = new node;
			root->right->parent = root;
			end = root->right;
		}
	}


	int bfactor(node* p) {
		return get_height(p->right) - get_height(p->left);
	}

	void fixheight(node* p) {
		unsigned char hl = get_height(p->left);
		unsigned char hr = get_height(p->right);
		p->height = (hl > hr ? hl : hr)+1;
	}

	node* rotateright(node* p) {
		node* q = p->left;
		p->left = q->right;
		if (p->left)
			p->left->parent = p;
		q->right = p;
		q->parent = p->parent;
		p->parent = q;
		fixheight(p);
		fixheight(q);
		return (q);
	}

	node* rotateleft(node* p) {
		node* q = p->right;
		p->right = q->left;
		if (p->right)
			p->right->parent = p;
		q->left = p;
		q->parent = p->parent;
		p->parent = q;
		fixheight(p);
		fixheight(q);
		return (q);
	}

	node* balance(node* p) {
		fixheight(p);
		if( bfactor(p)== 2)
		{
			if( bfactor(p->right) < 0 )
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if( bfactor(p)== -2)
		{
			if( bfactor(p->left) > 0  )
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p;
	}

	node* removemin(node *p)
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* removemax(node *p)
	{
		if (!p->right)
			return p->left;
		p->right = removemax(p->right);
		return (balance(p));
	}

	node* insert(node* prev, node* p, T k)
	{
		if( !p ) {
			node* tmp = new node(k);
			tmp->parent = prev;
			return tmp;
		}
		if( k < p->key )
			p->left = insert(p, p->left, k);
		else
			p->right = insert(p, p->right, k);
		return balance(p);
	}

	node* remove(node* p, T k)
	{
		if (!p)
			return 0;
		if(k < p->key)
			p->left = remove(p->left,k);
		else if(k > p->key)
			p->right = remove(p->right,k);	
		else
		{
			node *q = p->left;
			node *r = p->right;
			node *parents = p->parent;
			// node_alc.deallocate(p, 1);
			p = NULL;
			if (q)
			{
				node *max = findmax(q);
				max->left = removemax(q);
				max->right = r;
				if (max->right)
					max->right->parent = max;
				if (max->left)
					max->left->parent = max;
				max->parent = parents;
				return (balance(max));
			}
			else if (r)
			{
				node *min = findmin(r);
				min->right = removemin(r);
				min->left = q;
				if (min->left)
					min->left->parent = min;
				if (min->right)
					min->right->parent = min;
				min->parent = parents;
				return (balance(min));
			}
		}
		return p;
	}
public:

	node* findmin(node* p) const {
		return p->left ? findmin(p->left) : p;
	}

	node* findmin() const {
		return root->left ? findmin(root->left) : root;
	}

	node* findmax(node *p) const	{ 
		return p->right ? findmax(p->right) : p; 
	}

	void insert(T k)
	{
		take_phantom();
		if( !root ) {
			root = new node(k);
			push_phantom();
			return ;
		}
		if(k < root->key)
			root->left = insert(root, root->left, k);
		else
			root->right = insert(root, root->right, k);
		root = balance(root);
		push_phantom();
	}

	void remove(T k)
	{
		if (!root)
			return ;
		take_phantom();
		if(k < root->key)
			root->left = remove(root->left,k);
		else if(k > root->key)
			root->right = remove(root->right,k);	
		else
		{
			node *q = root->left;
			node *r = root->right;
			node *parents = root->parent;
			root = NULL;
			if (q)
			{
				node *max = findmax(q);
				max->left = removemax(q);
				max->right = r;
				if (max->right)
					max->right->parent = max;
				if (max->left)
					max->left->parent = max;
				max->parent = parents;
				root = balance(max);
				push_phantom();
				return ;
			}
			else if (r)
			{
				node *min = findmin(r);
				min->right = removemin(r);
				min->left = q;
				if (min->left)
					min->left->parent = min;
				if (min->right)
					min->right->parent = min;
				min->parent = parents;
				root = balance(min);
				push_phantom();
				return ;
			}
		}
		root = balance(root);
		push_phantom();
	}

};

//CLASS MAP

template<class Key,
	class T,
	class Compare = ft::less<Key>,
	class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef ft::pair<const Key, T> value_type;
	typedef size_t size_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef value_type& reference;
	typedef const value_type const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef iterator<value_type> iterator;
private:
	avl_tree<value_type> container;
public:
	iterator begin() {
		return container.findmin();
	}
	iterator end() {
		return container.get_end();
	}
	std::pair<iterator, bool> insert( const value_type& value ) {
		iterator it = begin();
		for (; it != end(); ++it)
		{
			if (it->first == value.first)
				return (std::pair<iterator, bool>(it, 0));
		}
		container.insert(value);
		return (std::pair<iterator, bool>(it, 1));
	}

	void erase (iterator position) {
		container.remove(*position);
	}
	size_type erase (const key_type& k) {
		size_type count = 0;
		for (iterator it = begin(); it != end(); ++it)
		{
			if (it->first == k) {
				container.remove(*it);
				count++;
			}
		}
		return count;
	}
};

};