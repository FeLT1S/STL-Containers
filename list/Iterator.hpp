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
		iterator(Node *it) : _it(it) {}
		iterator(const iterator &copy) : _it(copy._it) {}
		iterator& operator=(const iterator &copy) {
			_it = copy._it;
			return *this;
		}
		reference operator*() { return _it->content; }
		iterator operator++() { 
			_it = _it->next;
			return *this; 
		}
		iterator operator--() { 
			_it = _it->prev;
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
	};
};