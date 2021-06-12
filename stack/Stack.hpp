#pragma once 

# include "../list/List.hpp"

namespace ft {
	template <class T, class Container = ft::list<T> >
	class stack {
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

			explicit			stack(const Container &cont = Container())
			{
				_cont = cont;
			}
			bool				empty() const { return (_cont.empty()); }
			size_type			size() const { return (_cont.size()); }
			value_type			&top() { return (_cont.back()); }
			const value_type	&top() const { return (_cont.back()); }
			void				push(const value_type &val) { _cont.push_back(val); }
			void				pop() { _cont.pop_back(); }

		protected:
			container_type _cont;

  	friend bool operator== (const stack& lhs, const stack& rhs) { return (lhs._cont == rhs._cont); }

	friend bool operator!= (const stack& lhs, const stack& rhs) { return (lhs._cont != rhs._cont); }

  	friend bool operator< (const stack& lhs, const stack& rhs) { return (lhs._cont < rhs._cont); }
	
  	friend bool operator<= (const stack& lhs, const stack& rhs) { return (lhs._cont <= rhs._cont); }
	
  	friend bool operator> (const stack& lhs, const stack& rhs) { return (lhs._cont > rhs._cont); }
	
  	friend bool operator>= (const stack& lhs, const stack& rhs) { return (lhs._cont >= rhs._cont); }
	};
}
