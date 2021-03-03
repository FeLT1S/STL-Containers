#include "List.hpp"

int main()
{
	ft::list<int> lst;
	lst.push_back(145);
	lst.push_back(148);
	lst.push_front(15);
	for (ft::list<int>::iterator _it = lst.begin(); _it != lst.end(); ++_it)
		std::cout << *_it << std::endl;
	
	return 0;
}