#pragma once

#include <iostream>
#include <memory>
#include "Iterator.hpp"

namespace ft
{
	template< class T, class Allocator = std::allocator<T> >
	class list
	{
	public:
		struct s_node {
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::pointer pointer;

			allocator_type __alloc;
			value_type *__content;
			struct s_node *__prev;
			struct s_node *__next;

			s_node() : __prev(NULL), __next(NULL), __content(new value_type) {*__content = T();}
			s_node(const Allocator& alloc) : __alloc(alloc), __prev(NULL), __next(NULL) , __content(__alloc.allocate(1)) {}
			s_node(T cont) : __prev(NULL), __next(NULL), __content(cont) {}
			~s_node() {delete __content;}
		};
		typedef reverse_iterator<struct s_node, T> reverse_iterator;
		typedef iterator<struct s_node, T> iterator;
		typedef	std::allocator<s_node>	node_allocator;
		typedef size_t size_type;
	protected:
		node_allocator _node_alloc;
		struct s_node* _head;
		struct s_node* _tail;
	public:
		list() : _head(_node_alloc.allocate(1)), _tail(_head) {
			_node_alloc.construct(_head);
		}

		explicit list(const Allocator& alloc) : _head(_node_alloc.allocate(1)), _tail(_head) {
			_head->__content = alloc.allocate(1);
		}

		explicit list(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) {}

		template< class InputIt >
		list( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) {
			_node_alloc.construct(_head);
		}

		list( const list& copy ) : _head(_node_alloc.allocate(1)), _tail(_head) {
			_node_alloc.construct(_head);
			for (s_node * tmp = copy._head; tmp != copy._tail; tmp = tmp->__next)
				push_back(*tmp->__content);
		}

		~list() {
			clear();
			_node_alloc.destroy(_tail);
			_node_alloc.deallocate(_tail, 1);
		}

		list& operator=(const list& copy) {
			if (_head != _tail) {
				clear();
			}
			for (s_node * tmp = copy._head; tmp != copy._tail; tmp = tmp->__next)
				push_back(*tmp->__content);
			return *this;
		}

		iterator begin() {
			return iterator(_head);
		}

		iterator end() {
			return iterator(_tail);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(_tail->__prev);
		}

		reverse_iterator rend() {
			return reverse_iterator(_head->__prev);
		}

		void clear() {
			while (_head != _tail)
				erase(_head);
		}

		bool empty() const {return _head == _tail;}

		size_type size() const {
			size_type i = 0;
			for (s_node *tmp = _head; tmp != _tail; tmp = tmp->__next)
				++i;
			return i;
		}

		size_type max_size() const {return _node_alloc.max_size();}

		iterator insert( iterator pos, const T& value ) {
			if (pos == _head)
			{
				push_front(value);
				return begin();
			}
			else {
				s_node *new_node;
				new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node);

				iterator prev = pos->__prev;
				*new_node->__content = value;
				new_node->__prev = pos->__prev;
				new_node->__next = prev->__next;

				pos->__prev = new_node;
				prev->__next = new_node;
				return new_node;
			}
		}

		void insert( iterator pos, size_type count, const T& value ) {
			for (size_type i = 0; i < count; i++)
				insert(pos, value);
		}

		void insert( iterator pos, iterator first, iterator last) {
			while (first != last)
				insert(pos, *first++);
		}

		iterator erase( iterator pos ) {
			if (pos->__prev)
				pos->__prev->__next = pos->__next;
			else
				_head = pos->__next;
			s_node *tmp = pos->__prev;
			++pos;
			_node_alloc.destroy(pos->__prev);
			_node_alloc.deallocate(pos->__prev, 1);
			pos->__prev = tmp;
			return pos;
		}

		iterator erase( iterator first, iterator last ) {
			while (first != last)
				erase(first++);
			return last;
		}

		void pop_front() {
			erase(_head);
		}

		void pop_back() {
			erase(_tail->__prev);
		}

		void push_back(T value) {
			*_tail->__content = value;
			s_node *node = _node_alloc.allocate(1);
			_node_alloc.construct(node);
			_tail->__next = node;
			node->__next = NULL;
			node->__prev = _tail;
			_tail = node;
		}

		void push_front(T value) {
			s_node *node = _node_alloc.allocate(1);
			_node_alloc.construct(node);
			_head->__prev = node;
			node->__next = _head;
			node->__prev = NULL;
			*node->__content = value;
			_head = node;
		}

		void resize( size_type count, T value = T() ) {
			size_type len = size();

			if (count > len)
				while (++len <= count)
					push_back(value);
			else
			{
				iterator it = begin();
				for (size_type i = 0; i < count; ++i)
					++it;
				erase(it, end());
			}
		}

		void swap( list& other ) {
			std::swap(_head, other._head);
			std::swap(_tail, other._tail);
		}

		void merge( list& other ) {
			s_node *tmp = _head;
			std::cout << (other._head == other._tail) <<std::endl;
			for (iterator it = begin(); it != end(); ++it)
				std::cout << *it << std::endl;
		}
		template <class Compare>
		void merge( list& other, Compare comp );
	};
};