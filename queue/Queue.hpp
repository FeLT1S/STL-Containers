#pragma once

#include "../list/List.hpp"

namespace ft
{
	template<class T, class Container = ft::list<T> >
	class queue
	{
		private:
			Container _cont;
		public:

		typedef	T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;
			
		explicit queue (const container_type &cont = container_type())
		{
			_cont = cont;
		}

		bool				empty() const { return (_cont.empty()); }
		size_type			size() const { return (_cont.size()); }
		void				push(const value_type &val) { _cont.push_back(val); }
		void				pop() { _cont.pop_front(); }
		value_type			&front() { return (*_cont.begin()); }
		value_type const	&front() const { return (*_cont.begin()); }
		value_type			&back() { return (*_cont.rbegin()); }
		value_type const	&back() const { return (*_cont.rbegin()); }

  	friend bool operator== (const queue& lhs, const queue& rhs) { return (lhs._cont == rhs._cont); }

	friend bool operator!= (const queue& lhs, const queue& rhs) { return (lhs._cont != rhs._cont); }

  	friend bool operator< (const queue& lhs, const queue& rhs) { return (lhs._cont < rhs._cont); }
	
  	friend bool operator<= (const queue& lhs, const queue& rhs) { return (lhs._cont <= rhs._cont); }
	
  	friend bool operator> (const queue& lhs, const queue& rhs) { return (lhs._cont > rhs._cont); }
	
  	friend bool operator>= (const queue& lhs, const queue& rhs) { return (lhs._cont >= rhs._cont); }
	};
}