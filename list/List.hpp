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
			T content;
			struct s_node *prev;
			struct s_node *next;
		};
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::pointer pointer;
		typedef iterator<struct s_node, T> iterator;
		typedef size_t size_type;
	protected:
		struct s_node* _head;
		struct s_node* _tail;
	public:
		list() : _head(new struct s_node) {
			_head->prev = NULL;
			_head->next = NULL;
			_head->content = 0;
			_head = _tail;
		}

		explicit list(const Allocator& alloc) {
			alloc.allocate(sizeof(list));
		}

		explicit list(size_type count, const T& value = T(), const Allocator& alloc = Allocator()) {}

		iterator begin() {
			return iterator(_head);
		}
		iterator end() {
			return iterator(_tail);
		}

		void push_back(T value) {
			_tail->content = value;
			struct s_node *node = new struct s_node;
			_tail->next = node;
			node->next = NULL;
			node->prev = _tail;
			_tail = node;
		}
		void push_front(T value) {
			struct s_node *node = new struct s_node;
			_head->prev = node;
			node->next = _head;
			node->prev = NULL;
			node->content = value;
			_head = node;
		}
	};
};