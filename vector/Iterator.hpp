#pragma once

#include "Vector.hpp"

namespace ft
{
	template<class T>
	class iterator {
public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef size_t size_type;
	
		template <template <typename> class const_iterator>
		operator const_iterator<const value_type>() {
			return const_iterator<const value_type>((pointer)_it);
		}
	private:
		pointer _it;
	public:
		iterator() : _it(NULL) {}
		iterator(pointer it) : _it(it) {}
		iterator(const iterator &copy) : _it(copy._it) {}
		// node *getData() {return _it;}
		iterator& operator=(const iterator &copy) {
			_it = copy._it;
			return *this;
		}
		reference operator*() { return *_it; }
		iterator operator++() { 
			_it = _it + 1;
			return *this; 
		}
		iterator operator--() { 
			_it = _it - 1;
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

		iterator operator+(size_type numb) {
			return _it + numb;;
		}

		iterator operator-(size_type numb) {
			return _it - numb;
		}

		long operator-(iterator it2) {
			return _it - it2._it;
		}

		iterator operator+=(size_type numb) {
			_it = _it + numb;
			return *this;
		}

		iterator operator-=(size_type numb) {
			_it = _it - numb;
			return *this;
		}

		friend bool operator== (const iterator &c1, const iterator &c2) {
			return c1._it == c2._it;
		}
		friend bool operator!= (const iterator &c1, const iterator &c2) {
			return c1._it != c2._it;
		}
		pointer operator->() {return &_it;}
		reference operator[]( size_type pos ) const {return _it[pos];}
	};

//REVERSE

	template< class Iter >
	class reverse_iterator
	{
	public:
		typedef typename Iter::reference reference;
		typedef typename Iter::pointer pointer;
		typedef Iter iterator_type;
		typedef size_t size_type;
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

		reverse_iterator operator+(size_type numb) {
			return _it - numb;
		}

		reverse_iterator operator-(size_type numb) {
			return _it + numb;
		}

		long operator-(reverse_iterator it2) {
			return it2._it - _it;
		}

		reverse_iterator operator+=(size_type numb) {
			return _it -= numb;
		}

		reverse_iterator operator-=(size_type numb) {
			return _it += numb;
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
		reference operator[]( size_type pos ) {
			return *(_it - (pos + 1));}
	};
};