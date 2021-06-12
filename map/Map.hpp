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

template< class T >
void swap( T& lhs, T& rhs ) {
	T buff = lhs;
	lhs = rhs;
	rhs = buff;
}

//PAIR

template<class Pair, class KeyComp>
struct pair_comp
{
    KeyComp _kcomp;

    pair_comp(const KeyComp& kc = KeyComp()) : _kcomp(kc) {}

    bool operator()(const Pair& p1, const Pair& p2) const
    {
        return _kcomp(p1.first,p2.first);
    }
};

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
	~pair() {}
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

template <typename T>
struct node {
		T key;
		unsigned char height;
		node* left;
		node* right;
		node* parent;
		node() : key(T()) {left = right = 0; height = 1; parent = 0;}
		node(T k) : key(k) {left = right = 0; height = 1; parent = 0;}
		node(const node& copy) : key(copy.key), height(copy.height), left(copy.left), right(copy.right), parent(copy.parent) {}
};

//AVL_TREE
template<typename T, class Allocator, class Comp>
class avl_tree {
public:
	typedef node<T> node;
	typedef Allocator allocator_type;
	typedef typename allocator_type::template rebind<node>::other	node_alloc_type;
private:
	Comp comp;
	node_alloc_type node_alloc;
	allocator_type alloc;
	node *root;
	node *end;
public:
	avl_tree() : root(node_alloc.allocate(1)), end(root) {node_alloc.construct(root);}

	node *copy_tree(node *prev,node * node_) {
		if (node_ == NULL)
			return NULL;
		node *newnode = node_alloc.allocate(1);
		node_alloc.construct(newnode, node_->key);
		newnode->parent = prev;
		newnode->height = node_->height;
		newnode->left = copy_tree(newnode, node_->left);
		newnode->right = copy_tree(newnode, node_->right);
		return newnode;
	}

	avl_tree(const avl_tree& copy) {
		root = copy_tree(NULL, copy.root);
		end = findmax(root);
	}
	avl_tree& operator= (const avl_tree& x) {
		if (root)
			clear_tree();
		root = copy_tree(NULL, x.root);
		end = findmax(root);
		return *this;
	}

	unsigned char get_height(node* p) {
		return p ? p->height : 0;
	}
	node *get_end() const{
		return end;
	}
private:
	void take_phantom(node *p) {
		if (p->right)
			take_phantom(p->right);
		else {
			p->parent->right = 0;
		}
	}

	void take_phantom() {
		if (!root)
			return ;
		if (!root->left && !root->right) {
			root = NULL;
			return ;
		}
		if (root->right)
			take_phantom(root->right);
	}

	void push_phantom(node *p) {
		if (p->right)
			push_phantom(p->right);
		else {
			p->right = end;
			end->parent = p;
		}
	}

	void push_phantom() {
		if (!root) {
			root = end;
			end->parent = NULL;
			return ;
		}
		if (root->right)
			push_phantom(root->right);
		else {
			root->right = end;
			end->parent = root;
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
			p = node_alloc.allocate(1);
			node_alloc.construct(p, k);
			p->parent = prev;
			return p;
		}
		if( comp(k.first, root->key.first) )
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
			alloc.destroy(&p->key);
			node_alloc.deallocate(p, 1);
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

	void insert(node *elem, T k)
	{
		take_phantom();
		if( !elem ) {
			elem = node_alloc.allocate(1);
			node_alloc.construct(elem, k);
			push_phantom();
			return ;
		}
		if(comp(k.first, root->key.first))
			elem->left = insert(elem, elem->left, k);
		else
			elem->right = insert(elem, elem->right, k);
		elem = balance(elem);
		push_phantom();
	}

	void insert(T k)
	{
		take_phantom();
		if( !root ) {
			root = node_alloc.allocate(1);
			node_alloc.construct(root, k);
			push_phantom();
			return ;
		}
		if(comp(k.first, root->key.first))
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
		if(comp(k.first, root->key.first))
			root->left = remove(root->left,k);
		else if( !comp(k.first, root->key.first))
			root->right = remove(root->right,k);	
		else
		{
			node *q = root->left;
			node *r = root->right;
			node *parents = root->parent;
			alloc.destroy(&root->key);
			node_alloc.deallocate(root, 1);
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
		// root = balance(root);
		push_phantom();
	}

	void clear_tree(node *node) {
		if (node->left) clear_tree(node->left);
		if (node->right) clear_tree(node->right);
		alloc.destroy(&node->key);
		node_alloc.deallocate(node, 1);
	}

	void clear_tree() {
		clear_tree(root);
	}

	~avl_tree() {
		clear_tree(root);
	}

	size_t max_size() const {
		return node_alloc.max_size();
	}
};

//CLASS MAP

template<class Key,
	class T,
	class Compare = std::less<Key>,
	class Allocator = std::allocator<std::pair<const Key, T> > >
class map {
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef std::pair<const Key, T> value_type;
	typedef size_t size_type;
	typedef Compare key_compare;
	typedef pair_comp<value_type, key_compare> value_compare;
	typedef Allocator allocator_type;
	typedef value_type& reference;
	typedef const value_type const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef iterator<const value_type> const_iterator;
	typedef iterator<value_type> iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
private:
	avl_tree<value_type, allocator_type, Compare> _container;
	key_compare _comp;
	allocator_type _alloc;
	size_type _size;

public:
	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _comp(comp), _alloc(alloc), _size(0) {}

	template <typename _Val, template< typename > class  _InputIterator>
	map (_InputIterator <_Val > first, _InputIterator <_Val > last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _comp(comp), _alloc(alloc) {
		while (first != last) {
			_container.insert(*first++);
			++_size;
		}
	}

	map (const map& x) : _size(x._size) {
		for (const_iterator it = x.begin(); it != x.end(); it++)
			_container.insert(*it);
	}

	~map() {}

	map& operator= (const map& x) {
		for (const_iterator it = x.begin(); it != x.end(); it++) {
			_container.insert(*it);
			++_size;
		}
		return *this;
	}
	iterator begin() {
		return _container.findmin();
	}
	iterator end() {
		return _container.get_end();
	}

	const_iterator begin() const {
		return iterator(_container.findmin());
	}

	const_iterator end() const {
		return iterator(_container.get_end());
	}

    reverse_iterator rbegin() {
		return reverse_iterator(_container.get_end());}

	const_reverse_iterator rbegin() const {
		return reverse_iterator(_container.get_end());
	}

    reverse_iterator rend() {
		return reverse_iterator(_container.findmin());
	}
	const_reverse_iterator rend() const {
		return reverse_iterator(_container.findmin());
	}

	bool empty() const {
		return !(_size);
	}

	size_type size() const {
		return _size;
	}

	size_t max_size() const {
		return _container.max_size();
	}

	mapped_type& operator[] (const key_type& k) {
		for(iterator i = begin(); i != end(); ++i) {
			if (i->first == k)
				return i->second;
		}
		return insert(value_type(k, mapped_type())).first->second;
	}

	std::pair<iterator, bool> insert( const value_type& value ) {
		iterator it = begin();
		while (it != end())
		{
			if (it->first == value.first)
				return (std::pair<iterator, bool>(it, 0));
			++it;
		}
		_container.insert(value);
		++_size;
		it = begin();
		while (it != end())
		{
			if (it->first == value.first)
				break ;
			++it;
		}
		return (std::pair<iterator, bool>(it, 1));
	}

	iterator insert(iterator position, const value_type& val) {
		iterator next = position--;
		if (position.getData() && position->first < val.first && next->first > val.first) {
			_container.insert(position.getData(), val);
			return ++position;
		}
		else
			return insert(val).first;
	}

	template <typename _Val, template< typename > class  _InputIterator>
	void insert(_InputIterator <_Val > first, _InputIterator <_Val > last) {
		while (first != last)
		{
			_size++;
			_container.insert(*first++);
		}
	}

	void erase(iterator position) {
		_container.remove(*position);
		--_size;
	}

	size_type erase(const key_type& k) {
		size_type count = 0;
		for (iterator it = begin(); it != end(); ++it)
		{
			if (it->first == k) {
				_container.remove(*it);
				count++;
				--_size;
			}
		}
		return count;
	}

	void erase(iterator first, iterator last) {
		while (first != last) {
			iterator tmp = first++;
			erase(tmp);
		}
	}

	void swap(map& x) {
		ft::swap(_container, x._container);
		ft::swap(_size, x._size);
	}

	void clear() {
		erase(begin(), end());
	}

	key_compare key_comp() const {
		return _comp;
	}

	value_compare value_comp() const {
		return _comp;
	}

	allocator_type get_allocator() const {
		return _alloc;
	}

	iterator find(const key_type& k) {
		iterator i = begin();
		for (; i != end(); ++i) {
			if (i->first == k)
				break ;
		}
		return i;
	}

	const_iterator find(const key_type& k) const {
		const_iterator i = begin();
		for (; i != end(); ++i) {
			if (i->first == k)
				break ;
		}
		return i;
	}

	size_type count(const key_type& k) const {
		size_type count = 0;
		for (const_iterator i = begin(); i != end(); ++i) {
			if (i->first == k)
				++count;
		}
		return count;
	}

	iterator lower_bound(const key_type& k) {
		iterator i = begin();
		while (i != end() && _comp(i->first, k))
			++i;
		return i;
	}

	const_iterator lower_bound(const key_type& k) const {
		const_iterator i = begin();
		while (i != end() && _comp(i->first, k))
			++i;
		return i;
	}

	iterator upper_bound(const key_type& k) {
		iterator i = begin();
		while (i != end() && _comp(i->first, k))
			++i;
		if (i != end())
			++i;
		return i;
	}

	const_iterator upper_bound(const key_type& k) const {
		const_iterator i = begin();
		while (i != end() && _comp(i->first, k))
			++i;
		if (i != end() && i->first != k)
			++i;
		return i;
	}

	std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
		return std::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));
	}

	std::pair<iterator,iterator> equal_range(const key_type& k) {
		return std::pair<iterator,iterator>(lower_bound(k), upper_bound(k));
	}

			friend bool operator==( const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs ) {
			const_iterator i = lhs.begin();
			const_iterator j = rhs.begin();

			while (i != lhs.end() && j != rhs.end())
			{
				if (i->first != j->first)
					return false;
				++i;
				++j;
			}
			if (i != lhs.end() || j != rhs.end())
				return false;
			return true;
		}

		friend bool operator!=( const ft::map<Key, T, Compare, Allocator>& lhs,
        const ft::map<Key, T, Compare, Allocator>& rhs ) {
			return !(lhs == rhs);
		}

		friend bool operator<( const ft::map<Key, T, Compare, Allocator>& lhs,
            const ft::map<Key, T, Compare, Allocator>& rhs ) {
			if (lhs.size() < rhs.size())
				return true;
			else if (lhs.size() > rhs.size())
				return false;
			else {
				const_iterator j = rhs.begin();
				for (const_iterator i = lhs.begin(); i != lhs.end(); ++i) {
					if (i->first < j->first)
						return true;
					if (i->first > j->first)
						return false;
					++j;
				}
				return false;
			}
		}
	
		friend bool operator<=( const ft::map<Key, T, Compare, Allocator>& lhs,
        	const ft::map<Key, T, Compare, Allocator>& rhs ) {
			return !(rhs < lhs);
		}

		friend bool operator>( const ft::map<Key, T, Compare, Allocator>& lhs,
            const ft::map<Key, T, Compare, Allocator>& rhs ) {
			return rhs < lhs;
		}
		
		friend bool operator>=( const ft::map<Key, T, Compare, Allocator>& lhs,
			const ft::map<Key, T, Compare, Allocator>& rhs ) {
			return !(lhs < rhs);
		}
};

};