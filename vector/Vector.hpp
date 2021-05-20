#pragma once

#include <iostream>
#include <memory>
#include "Iterator.hpp"
#include <cstring>

namespace ft {

	template<class T, class Allocator = std::allocator<T> > 
	class vector {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef Allocator allocator_type;
		typedef size_t size_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef iterator<const T> const_iterator;
		typedef iterator<T> iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
	public:
		allocator_type _alloc;
		size_type _capacity;
		size_type _size;
		pointer _array;
	public:
		//CONSTRUCTORS, DESTRUCTOR

		vector() : _size(0), _capacity(0), _array(_alloc.allocate(0)) {}
		explicit vector( const Allocator& alloc ) : _alloc(alloc), _size(0), _capacity(0), _array(_alloc.allocate(0)) {}

		explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) :
		_alloc(alloc), _size(count), _capacity(count), _array(_alloc.allocate(_capacity + 1)) {
			for (size_type i = 0; i != count; ++i)
				_alloc.construct(&_array[i], value);
		}

		template <typename _Val, template< typename > class  _InputIterator>
		vector( _InputIterator <_Val> first, _InputIterator <_Val> last, const Allocator& alloc = Allocator() ) :
		_alloc(alloc), _size(0), _capacity(0), _array(_alloc.allocate(_capacity + 1)) {
			insert(begin(), first, last);
		}
		vector( const vector& other ) :
		_alloc(other._alloc), _size(other._size), _capacity(other._capacity), _array(_alloc.allocate(_capacity + 1)) {
			for (size_type i = 0; i < _size; ++i)
				_alloc.construct(_array + i, other._array[i]);
		}

		void assign( size_type count, const T& value ) {
			clear();
			_alloc.deallocate(_array, _capacity + 1);
			_array = _alloc.allocate(count + 1);
			if (count > _capacity)
				_capacity = count;
			while (count--)
				push_back(value);
		}
		template <typename _Val, template< typename > class  _InputIterator>
		void assign( _InputIterator <_Val> first, _InputIterator <_Val> last ) {
			if (last - first < 0) {
				clear();
				// _alloc.deallocate(_array, _capacity + 1);
				_capacity = 0;
				throw std::length_error("vector");
				// return ;
			}

			long count = 0;
			// if (&(*last) <= _array + _size && &(*first) >= _array)
			count = &(*last) - &(*first);
			vector<T> tmp;
			while (first != last)
				tmp.push_back(*first++);
			iterator tmp_first = tmp.begin(); 
			iterator tmp_last = tmp.end();

			clear();
			_alloc.deallocate(_array, _capacity + 1);
			_array = _alloc.allocate(count + 1);
			if (count > _capacity)
				_capacity = count;
			iterator pos = begin();
			while (tmp_first != tmp_last)
				pos = insert(pos, *tmp_first++); 
		}

		allocator_type get_allocator() const {
			return _alloc;
		}

		vector& operator=(const vector& copy) {
			assign(copy.begin(), copy.end());
			return *this;
		}

		~vector() {
			for (size_type i = 0; i < _size; ++i)
				_alloc.destroy(_array + i);
			_alloc.deallocate(_array, _capacity + 1);
		}

		//MODIFIED

		bool empty() const {
			return _size == 0;
		}

		void clear() {
			for (iterator it = begin(); it != end(); ++it) {
				_alloc.destroy(&(*it));
				*it = T();
			}
			_size = 0;
		}

		void push_back( const T& value ) {
			insert(end(), value);
		}

		iterator insert( iterator pos, const T& value ) {
			unsigned long tmp = 0;
			bool check = false;
			if (_capacity == 0)
			{
				add_capacity(1);
				pos = begin();
			}
			else if (_size + 1 > _capacity) {
				if (&value >= _array && &value <= _array + _size && (check = true))
					tmp = &value - _array;
				long size = pos - begin();
				add_capacity(1);
				pos = begin() + size;
			}
			size_type i = &(*pos) - _array;
			std::memmove((void*)&_array[i + 1], (void*)&_array[i], (_size - i) * sizeof(value_type));
			if (!check)
				_alloc.construct(&(*pos), value);
			else
				_alloc.construct(&(*pos), _array[tmp]);
			++_size;
			return ++pos;
		}

		void insert( iterator pos, size_type count, const T& value ) {
			T tmp;
			// if (&value >= _array && &value <= _array + _size)
				tmp = value;
			while (count--)
				pos = insert(pos, tmp);
		}

		template <typename _Val, template< typename > class  _InputIterator>
		void insert( iterator pos, _InputIterator <_Val> first, _InputIterator <_Val> last) {
			if (last - first < 0)
				throw std::length_error("vector");
			vector<T> tmp;
			while (first != last)
				tmp.push_back(*first++);
			iterator tmp_first = tmp.begin(); 
			iterator tmp_last = tmp.end();
			while (tmp_first != tmp_last)
				pos = insert(pos, *tmp_first++); 
		}

		iterator erase( iterator pos ) {
			_alloc.destroy(&(*pos));
			for (size_type i = &(*pos) - _array; i < _size - 1; ++i)
				_alloc.construct(_array + i, _array[i + 1]);
			_alloc.destroy(_array + --_size);
			return pos;
		}

		iterator erase( iterator first, iterator last ) {
			while (first != last) {
				erase(first);
				--last;
			}
			return first;
		}

		void pop_back() {
			erase(end() - 1);
		}

		void swap( vector& other ) {
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(_array, other._array);
			std::swap(_alloc, other._alloc);
		}

		void resize( size_type count, value_type value = value_type() ) {
			if (count < _size) {
				erase(&_array[count], end());
			}
			else if (count > _size) {
				add_capacity(count - _size);
				for (size_type i = _size; i != count; ++i)
					push_back(value);
			}
			_size = count;
		}

		//ACCESS

		reference at( size_type pos ) {
			if (pos > _size)
				throw std::out_of_range("vector");
			return _array[pos];
		}
		const_reference at( size_type pos ) const {
			if (pos > _size)
				throw std::out_of_range("vector");
			return _array[pos];
		}
		reference operator[]( size_type pos ) {return _array[pos];}
		const_reference operator[]( size_type pos ) const {return _array[pos];}
		reference front() {return _array[0];}
		const_reference front() const {return _array[0];}
		reference back() {return _array[_size - 1];}
		const_reference back() const {return _array[_size - 1];}

		//ITERATORS

		iterator begin() {
			return iterator(_array);
		}
		const_iterator begin() const {
			return const_iterator(_array);
		}
		iterator end() {
			return iterator(_array + _size);
		}
		const_iterator end() const {
			return const_iterator(_array + _size);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(_array + _size);
		}
		const_reverse_iterator rbegin() const {
			return cosnt_reverse_iterator(_array + _size);
		}
		reverse_iterator rend() {
			return reverse_iterator(_array);
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(_array);
		}

		//CAPACITY
	private:
		void add_capacity(size_type added = 0) {
			size_type  new_capacity = _capacity == 0 ? 1 : _capacity;
			while (new_capacity < _capacity + added) {
				new_capacity *= 2;
			}
			if (new_capacity > max_size())
				throw std::length_error("vector");
			pointer tmp = _alloc.allocate(new_capacity + 1);
			for (size_type i = 0; i != _size; ++i)
				_alloc.construct(tmp + i, _array[i]);
			_alloc.deallocate(_array, _capacity + 1);
			_array = tmp;
			_capacity = new_capacity;
		}
	public:
		size_type capacity() const {
			return _capacity;
		}

		size_type max_size() const {
			return _alloc.max_size();
		}

		size_type size() const {
			return _size;
		}

		void reserve( size_type new_cap ) {
			if (new_cap > _capacity) {
				pointer tmp = _alloc.allocate(new_cap);
				for (size_type i = 0; i != _size; ++i)
					_alloc.construct(&tmp[i], _array[i]);
				_alloc.deallocate(_array, _capacity + 1);
				_array = tmp;
				_capacity = new_cap;
			}
		}

		friend bool operator==( const ft::vector<T,Allocator>& lhs, const ft::vector<T,Allocator>& rhs ) {
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

		friend bool operator!=( const ft::vector<T,Allocator>& lhs,
            const ft::vector<T,Allocator>& rhs ) {
			return !(lhs == rhs);
		}

		friend bool operator<( const ft::vector<T,Allocator>& lhs,
            const ft::vector<T,Allocator>& rhs ) {
			if (lhs.size() < rhs.size())
				return true;
			else if (lhs.size() > rhs.size())
				return false;
			else {
				for (size_type i = 0; i < lhs._size; ++i) {
					if (lhs[i] < rhs[i])
						return true;
					if (lhs[i] > rhs[i])
						return false;
				}
				return false;
			}
		}
	
		friend bool operator<=( const ft::vector<T,Allocator>& lhs,
        	const ft::vector<T,Allocator>& rhs ) {
			return !(rhs < lhs);
		}

		friend bool operator>( const ft::vector<T,Allocator>& lhs,
            const ft::vector<T,Allocator>& rhs ) {
			return rhs < lhs;
		}
		
		friend bool operator>=( const ft::vector<T,Allocator>& lhs,
			const ft::vector<T,Allocator>& rhs ) {
			return !(lhs < rhs);
		}
	};

};