#pragma once

#include "Map.hpp"

namespace ft
{
	template <typename T>
	struct node;

	template<class T>
	class iterator
	{
	public:
		typedef node<const T> const_node;
		typedef node<T> node;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

		template <template <typename> class const_iterator>
		operator const_iterator<const T>() { 
			return const_iterator<const T>((const_node *)_it); 
		}
	private:
		node *_it;

		node* findmin(node* p) const {
		return p->left ? findmin(p->left) : p;
		}
		node* findmax(node *p) const { 
		return p->right ? findmax(p->right) : p; 
		}
	public:
		iterator() : _it(NULL) {}
		iterator(node *it) : _it(it) {}
		node *getData() {return _it;}
		iterator(const iterator &copy) : _it(copy._it) {}
		iterator& operator=(const iterator &copy) {
			_it = copy._it;
			return *this;
		}
		reference operator*() const { return _it->key; }
		iterator operator++() {
			if (_it->right)
				_it = findmin(_it->right);
			else {
				while (_it->parent && _it->parent->right == _it)
					_it = _it->parent;
				_it = _it->parent;
			}
			return (*this);
		}
		iterator operator--() { 
			if (_it->left)
				_it = findmax(_it->left);
			else {
				while (_it->parent && _it->parent->left == _it)
					_it = _it->parent;
				_it = _it->parent;
			}
		return (*this);
		}
		iterator operator++(int) {
			iterator temp(*this);
			++(*this);
			return temp;
		}
		iterator operator--(int) {
			iterator temp(*this);
			--(*this);
			return temp;
		}
		friend bool operator== (const iterator &c1, const iterator &c2) {
			return c1._it == c2._it;
		}
		friend bool operator!= (const iterator &c1, const iterator &c2) {
			return c1._it != c2._it;
		}
		pointer operator->() {return &(_it->key);}
	};

	template<class T>
	struct node;

	template< class Iter >
	class reverse_iterator
	{
	public:
		typedef typename Iter::reference reference;
		typedef typename Iter::pointer pointer;
		typedef Iter iterator_type;
		template <template <typename> class const_reverse_iterator>
		operator const_reverse_iterator<iterator_type>() {
			return const_reverse_iterator<iterator_type>(_it);
		};
	private:
		iterator_type _it;
	public:
		reverse_iterator() : _it(NULL) {}
		reverse_iterator(const iterator_type &it) : _it(it) {}
		reverse_iterator(const reverse_iterator &copy) : _it(copy._it) {}

		reverse_iterator& operator=(const reverse_iterator &copy) {
			_it = copy._it;
			return *this;
		}
		reference operator*() {
			iterator_type tmp(_it);
			--tmp;
			return *tmp; 
		}

		reverse_iterator operator++() { 
			return --_it;
		}
		reverse_iterator operator--() { 
			return ++_it;
		}
		reverse_iterator operator++(int) {
			return _it--;
		}
		reverse_iterator operator--(int) {
			return _it++;
		}

		iterator_type base() {
			return _it;
		}

		friend bool operator== (const reverse_iterator &c1, const reverse_iterator &c2) {
			return c1._it == c2._it;
		}
		friend bool operator!= (const reverse_iterator &c1, const reverse_iterator &c2) {
			return c1._it != c2._it;
		}
		pointer operator->() {
			iterator_type tmp(_it);
			--tmp;
			return &(*tmp);
		}
	};
};