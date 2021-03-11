#pragma once

#include "List.hpp"

namespace ft
{
	template<typename Node, typename T>
	class iterator
	{
	public:     
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
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

	template<typename Node, typename T>
	class const_iterator
	{
	public:     
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
	private:
		const Node *_it;
	public:
		const_iterator() : _it(NULL) {}
		const_iterator(Node *it) : _it(it) {}
		const_iterator(const const_iterator &copy) : _it(copy._it) {}
		Node *getData() {return _it;}
		reference operator*() { return *_it->__content; }
		friend bool operator== (const const_iterator &c1, const const_iterator &c2) {
			return c1._it == c2._it;
		}
		friend bool operator!= (const const_iterator &c1, const const_iterator &c2) {
			return c1._it != c2._it;
		}
		T *operator->() {return _it->__content;}
	};

	template<typename Node, typename T>
	class reverse_iterator
	{
	public:     
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
	private:
		Node *_it;
	public:
		reverse_iterator() : _it(NULL) {}
		reverse_iterator(Node *it) : _it(it) {}
		reverse_iterator(const reverse_iterator &copy) : _it(copy._it) {}

		reverse_iterator& operator=(const reverse_iterator &copy) {
			_it = copy._it;
			return *this;
		}
		reference operator*() { return *_it->__content; }

		reverse_iterator operator++() { 
			_it = _it->__prev;
			return *this; 
		}
		reverse_iterator operator--() { 
			_it = _it->__next;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator temp(*this);
			++(*this);
			return temp;
		}
		reverse_iterator operator--(int) {
			reverse_iterator temp(*this);
			--(*this);
			return temp;
		}

		friend bool operator== (const reverse_iterator &c1, const reverse_iterator &c2) {
			return c1._it == c2._it;
		}
		friend bool operator!= (const reverse_iterator &c1, const reverse_iterator &c2) {
			return c1._it != c2._it;
		}
		Node *operator->() {return _it->__content;}
	};
};