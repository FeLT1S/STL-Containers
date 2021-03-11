#pragma once

#include <iostream>
#include <memory>
#include "Iterator.hpp"

namespace ft
{
	template< class T, class Allocator>
	struct s_node {
		typedef struct s_node* ptr;
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::pointer pointer;

		allocator_type __alloc;
		value_type *__content;
		ptr __prev;
		ptr __next;

		s_node(const Allocator& alloc = Allocator())
		:  __alloc(alloc), 
		__prev(NULL), 
		__next(NULL), 
		__content(__alloc.allocate(1)){
			*__content = T();
		}
		~s_node() {	
			__alloc.destroy(__content);
			__alloc.deallocate(__content, 1);
		}
	};

	template< class T, class Allocator = std::allocator<T> >
	class list
	{
	public:
		typedef struct s_node<T, Allocator> s_node;
		typedef reverse_iterator<s_node, T> reverse_iterator;
		typedef iterator<s_node, T> iterator;
		typedef const_iterator<s_node, T> const_iterator;
		typedef	std::allocator<s_node>	node_allocator;
		typedef size_t size_type;
	protected:
		node_allocator _node_alloc;
		s_node* _head;
		s_node* _tail;
	public:
		list() : _head(_node_alloc.allocate(1)), _tail(_head) {
			_node_alloc.construct(_head);
		}

		explicit list(const Allocator& alloc) : _head(_node_alloc.allocate(1)), _tail(_head) {
			_head->__content = alloc.allocate(1);
		}

		explicit list(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : _head(_node_alloc.allocate(1)), _tail(_head) {
			_node_alloc.construct(_head);
			while (count--)
				push_back(value);
		}

		// template< class InputIt >
		// list( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) : _head(_node_alloc.allocate(1)), _tail(_head) {
		// 	_node_alloc.construct(_head);
		// }

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
			s_node * node = pos.getData();
			if (node == _head)
			{
				push_front(value);
				return begin();
			}
			else {
				s_node *new_node;
				new_node = _node_alloc.allocate(1);
				_node_alloc.construct(new_node);

				s_node * prev = node->__prev;
				*new_node->__content = value;
				new_node->__prev = node->__prev;
				new_node->__next = prev->__next;

				node->__prev = new_node;
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
			s_node * node = (pos++).getData();

			if (node->__prev)
				node->__prev->__next = node->__next;
			else
				_head = node->__next;
			s_node *tmp = node->__prev;
			node->__next->__prev = tmp;
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
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
			while (tmp != _tail && other._head != other._tail)
			{
				if (*tmp->__content > *other._head->__content)
					splice(tmp, other, other._head);
				else
					tmp = tmp->__next;
			}
			if (other._head != other._tail)
				splice(tmp, other);
		}

		template <class Compare>
		void merge( list& other, Compare comp );

		void splice( iterator pos, list& other ) {
			splice(pos, other, other.begin(), other.end());
		}

		void splice( iterator pos, list& other, iterator it ) {
			splice(pos, other, it, ++it);
		}

		void splice( iterator pos, list& other, iterator first, iterator last) {
			s_node *node_pos = pos.getData();
			s_node *node_first = first.getData();
			s_node *node_last = last.getData()->__prev;

			if (node_pos != _head)
				node_pos->__prev->__next = node_first;
			else
				_head = node_first;
			if (node_first != other._head)
				node_first->__prev->__next = node_last->__next;
			else
				other._head = node_last->__next;
			s_node *tmp = node_pos->__prev;
			node_pos->__prev = node_last;
			node_last->__next->__prev = node_first->__prev;
			node_first->__prev = tmp;
			node_last->__next = node_pos;
		}

		void reverse() {
			iterator it = begin();
			s_node *node = NULL;

			while (true)
			{
				node = it.getData();
				++it;
				if (it != end())
					std::swap(node->__next, node->__prev);
				else
					break ;
			}
			node->__next = node->__prev;
			node->__prev = NULL;
			s_node *tmp = _head;
			_head = node;
			node = it.getData();
			tmp->__next = node;
			node->__prev = _head;
		}
	};
};