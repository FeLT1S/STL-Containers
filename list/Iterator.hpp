#pragma once

#include "List.hpp"

namespace ft
{
	template<class T>
	struct s_node;

	template<class T>
	class iterator
	{
	public:
		typedef s_node<T> node;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>() {
			return const_iterator<const value_type>((s_node<const value_type>*)_it);
		}
	private:
		node *_it;
	public:
		iterator() : _it(NULL) {}
		iterator(node *it) : _it(it) {}
		iterator(const iterator &copy) : _it(copy._it) {}
		node *getData() {return _it;}
		iterator& operator=(const iterator &copy) {
			_it = copy._it;
			return *this;
		}
		reference operator*() { return _it->__content; }
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
		pointer operator->() {return &(_it->__content);}
	};

	template<class T>
	struct s_node;

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