#pragma once

#include <iostream>
#include <memory>
#include "Iterator.hpp"

namespace ft
{
	template< class T>
	struct s_node {
		typedef struct s_node* ptr;
		typedef T value_type;

		value_type __content;
		ptr __prev;
		ptr __next;
	};

	template< class T, class Allocator = std::allocator<T> >
	class list
	{
	public:
		typedef struct s_node<T> s_node;
		typedef iterator<const T> const_iterator;
		typedef iterator<T> iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef	std::allocator<s_node>	node_allocator;
		typedef size_t size_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
	protected:
		node_allocator _node_alloc;
		allocator_type alloc;
		s_node* _head;
		s_node* _tail;
		size_type _size;
	public:
		list() : _head(_node_alloc.allocate(1)), _tail(_head) {
			_head->__prev = NULL;
			_head->__next = NULL;
			_size = 0;
			alloc.construct(&_head->__content, T());
		}

		explicit list(const Allocator& _alloc) : _head(_node_alloc.allocate(1)), _tail(_head) {
			_head->__prev = NULL;
			_head->__next = NULL;
			_size = 0;
			alloc = _alloc;
			alloc.construct(&_head->__content, T());
		}

		explicit list(size_type count, const T& value = T(), const Allocator& _alloc = Allocator()) :
		_head(_node_alloc.allocate(1)), 
		_tail(_head) {
			_head->__prev = NULL;
			_head->__next = NULL;
			_size = 0;
			alloc = _alloc;
			while (count--)
				push_back(value);
		}

		template <typename _Val, template< typename > class  _InputIterator>
		list(_InputIterator <_Val > first, _InputIterator <_Val > last, const allocator_type& _alloc = allocator_type()) : 
		_head(_node_alloc.allocate(1)),
		_tail(_head)
		{
			_head->__prev = NULL;
			_head->__next = NULL;
			_size = 0;
			alloc = _alloc;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list( const list& copy ) : _head(_node_alloc.allocate(1)), _tail(_head) {
			_head->__prev = NULL;
			_head->__next = NULL;
			for (s_node * tmp = copy._head; tmp != copy._tail; tmp = tmp->__next)
				push_back(tmp->__content);
		}

		~list() {
			clear();
			_node_alloc.deallocate(_tail, 1);
		}

		list& operator=(const list& copy) {
			if (_head != _tail) {
				clear();
			}
			for (s_node * tmp = copy._head; tmp != copy._tail; tmp = tmp->__next)
				push_back(tmp->__content);
			return *this;
		}
		
		void assign ( size_type count, const T & value ) {
			if (_head != _tail) {
				clear();
			}
			while (count--)
				push_back(value);
		}

		void assign (iterator first, iterator last) {
			if (_head != _tail) {
				clear();
			}
			while (first != last)
				push_back(*(first++));
		}

		allocator_type get_allocator() const {
			return _head->__alloc;
		}

		const_reference front() const {
			return _head->__content;
		}

		const_reference back() const {
			return _tail->__prev->__content;
		}

		iterator begin() {
			return iterator(_head);
		}

		const_iterator begin() const {
			return iterator(_head);
		}

		iterator end() {
			return iterator(_tail);
		}

		const_iterator end() const{
			return iterator(_tail);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(_tail);
		}

		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(_tail);
		}

		reverse_iterator rend() {
			return reverse_iterator(_head);
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(_head);
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
				alloc.construct(&new_node->__content, value);

				s_node * prev = node->__prev;
				new_node->__content = value;
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

		iterator erase(iterator pos) {
			s_node * node = (pos++).getData();

			if (node->__prev)
				node->__prev->__next = node->__next;
			else
				_head = node->__next;
			s_node *tmp = node->__prev;
			node->__next->__prev = tmp;
			alloc.destroy(&node->__content);
			_node_alloc.deallocate(node, 1);
			return pos;
		}

		iterator erase( iterator first, iterator last ) {
			while (first != last)
				first = erase(first);
			return last;
		}

		void pop_front() {
			erase(_head);
		}

		void pop_back() {
			erase(_tail->__prev);
		}

		void push_back(T value) {
			s_node *node = _node_alloc.allocate(1);
			_tail->__next = node;
			node->__next = NULL;
			node->__prev = _tail;
			alloc.construct(&_tail->__content, value);
			_tail = node;
		}

		void push_front(T value) {
			s_node *node = _node_alloc.allocate(1);
			_head->__prev = node;
			node->__next = _head;
			node->__prev = NULL;
			alloc.construct(&node->__content, value);
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
				if (tmp->__content > other._head->__content)
					splice(tmp, other, other._head);
				else
					tmp = tmp->__next;
			}
			if (other._head != other._tail)
				splice(tmp, other);
		}

		template <class Compare>
		void merge( list& other, Compare comp ) {
			s_node *tmp = _head;
			while (tmp != _tail && other._head != other._tail)
			{
				if (comp(tmp->__content, other._head->__content))
					splice(tmp, other, other._head);
				else
					tmp = tmp->__next;
			}
			if (other._head != other._tail)
				splice(tmp, other);
		}

		void splice( iterator pos, list& other ) {
			splice(pos, other, other.begin(), other.end());
		}

		void splice( iterator pos, list& other, iterator it ) {
			splice(pos, other, it, ++it);
		}

		void splice( iterator pos, list& other, iterator first, iterator last) {
			if (other.size() < 1)
				return ;
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
			if (size() < 2)
				return ;
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

		void sort() {
			if (size() < 2)
				return ;
			for (iterator i = _head->__next; i != end(); ++i) {
				for (iterator j = i; j != begin() && j.getData()->__prev->__content > *j; --j) {
					T tmp = j.getData()->__prev->__content;
					j.getData()->__prev->__content = *j;
					*j = tmp;
				}
			}
		}

		template< class Compare >
		void sort( Compare comp ) {
			if (size() < 2)
				return ;
			for (iterator i = _head->__next; i != end(); ++i) {
				for (iterator j = i; j != begin() && !comp(j.getData()->__prev->__content, *j); --j) {
					T tmp = j.getData()->__prev->__content;
					j.getData()->__prev->__content = *j;
					*j = tmp;
				}
			}
		}

		void unique() {
			iterator i = begin();
			iterator j;

			while (i != end()) {
				j = i;
				++j;
				if (*i == *j)
					erase(j);
				else
					++i;
			}
		}

		template< class BinaryPredicate >
		void unique( BinaryPredicate p ) {
			iterator i = begin();
			iterator j;

			while (i != end()) {
				j = i;
				++j;
				if (p(*i, *j))
					erase(j);
				else
					++i;
			}
		}

		void remove( const T& value ) {
			iterator i = begin();

			while (i != end()) {
				if (*i == value)
					i = erase(i);
				else
					++i;
			}
		}

		template< class UnaryPredicate >
		void remove_if(UnaryPredicate p) {
			iterator i = begin();

			while (i != end()) {
			if (p(*i))
				i = erase(i);
			else
				++i;
			}
		}

		friend bool operator==( const ft::list<T,Allocator>& lhs, const ft::list<T,Allocator>& rhs ) {
			const_iterator i = lhs.begin();
			const_iterator j = rhs.begin();

			while (i != lhs.end() && j != rhs.end())
			{
				if (*i != *j)
					return false;
				++i;
				++j;
			}
			if (i != lhs.end() || j != rhs.end())
				return false;
			return true;
		}

		friend bool operator!=( const ft::list<T,Allocator>& lhs,
        const ft::list<T,Allocator>& rhs ) {
			return !(lhs == rhs);
		}

		friend bool operator<( const ft::list<T,Allocator>& lhs,
            const ft::list<T,Allocator>& rhs ) {
			if (lhs.size() < rhs.size())
				return true;
			else if (lhs.size() > rhs.size())
				return false;
			else {
				const_iterator j = rhs.begin();
				for (const_iterator i = lhs.begin(); i != lhs.end(); ++i) {
					if (*i < *j)
						return true;
					if (*i > *j)
						return false;
					++j;
				}
				return false;
			}
		}
	
		friend bool operator<=( const ft::list<T,Allocator>& lhs,
        	const ft::list<T,Allocator>& rhs ) {
			return !(rhs < lhs);
		}

		friend bool operator>( const ft::list<T,Allocator>& lhs,
            const ft::list<T,Allocator>& rhs ) {
			return rhs < lhs;
		}
		
		friend bool operator>=( const ft::list<T,Allocator>& lhs,
			const ft::list<T,Allocator>& rhs ) {
			return !(lhs < rhs);
		}
	};
};