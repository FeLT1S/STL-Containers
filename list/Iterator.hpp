#pragma once

#include "List.hpp"

namespace ft
{
	template<class T, class Allocator >
	struct s_node;

	template<class T, class Allocator>
	class iterator
	{
	public:
		typedef struct s_node<T, Allocator> Node;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

		template <template <typename, typename> class const_iterator>
		operator const_iterator<const value_type, Allocator>() {
			return const_iterator<const value_type, Allocator>((s_node<const value_type, Allocator>*)_it);
		}
	private:
		Node *_it;
	public:
		iterator() : _it(NULL) {}
		iterator(Node *it) : _it(it) {}
		iterator(const iterator &copy) : _it(copy._it) {}
		Node *getData() {return _it;}
		iterator& operator=(const iterator &copy) {
			_it = copy._it;
			return *this;
		}
		reference operator*() { return *_it->__content; }
		iterator operator++() { 
			_it = _it->__next;
			return *this; 
		}
		iterator operator--() { 
			_it = _it->__prev;
			return *this;
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
		T *operator->() {return _it->__content;}
	};

	template<class T, class Allocator>
	class reverse_iterator
	{
	public:
		typedef s_node<T, Allocator> Node;
		typedef iterator<T, Allocator> iterator;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
	private:
		iterator _it;
	public:
		reverse_iterator() : _it(NULL) {}
		reverse_iterator(const iterator &it) : _it(it) {}
		reverse_iterator(const reverse_iterator &copy) : _it(copy._it) {}

		reverse_iterator& operator=(const reverse_iterator &copy) {
			_it = copy._it;
			return *this;
		}
		reference operator*() {
			iterator tmp(_it);
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

		iterator base() {
			return _it;
		}

		friend bool operator== (const reverse_iterator &c1, const reverse_iterator &c2) {
			return c1._it == c2._it;
		}
		friend bool operator!= (const reverse_iterator &c1, const reverse_iterator &c2) {
			return c1._it != c2._it;
		}
		T *operator->() {return *_it;}
	};

	template<class T, class Allocator >
	struct s_node;
};