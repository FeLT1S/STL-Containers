#include "list/List.hpp"
#include <list>

void test_insert()
{
std::cout << "ITERATOR\n\n";
    ft::list<int> start;
    for (int i = 0; i < 11; i++)
        start.push_back(i);
    ft::list<int> last;
    for (int i = -1; i > -11; i--)
        last.push_back(i);
    ft::list<int>::iterator it1 = start.begin();
    ft::list<int>::iterator it2 = start.end();
    ft::list<int>::iterator it3 = last.begin();
    last.insert(it3, it1, it2);
    ft::list<int>::iterator it4 = last.end();
    it3 = last.begin();
    ft::list<int>::iterator it31 = it3;
    ft::list<int>::iterator it32 = it3;
    for (int i = 0; i < 3; i++)
        ++it32;
    last.erase(++it31, it32);
    last.pop_back();
    last.pop_front();
    it3 = last.begin();
    while (it3 != it4)
        std::cout << *it3++ << " ";
    //last.clear();
    std::cout << "\n";
}

void test_swap()
{
    std::cout << "SWAP\n";
    ft::list<std::string> lst1;
    ft::list<std::string> lst2;

    lst1.push_back("123");
    lst1.push_back("321");
    lst2.push_back("1234");
    lst2.push_back("4321");
    lst2.swap(lst1);
    for (ft::list<std::string>::reverse_iterator it = lst2.rbegin(); it != lst2.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    //lst2.clear();
    //std::cout << lst2.empty() << std::endl;
    lst2.resize(10);
    for (ft::list<std::string>::reverse_iterator it = lst2.rbegin(); it != lst2.rend(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void test_merge()
{
	ft::list<int> test1;
	ft::list<int> test2;
	for (int i = 10; i > 0; i--)
		test1.push_back(i);
	ft::list<int>::iterator it1 = test1.begin();
	ft::list<int>::iterator it2 = test1.end();
	std::cout << "test1 : ";
	while (it1 != it2)
		std::cout << *it1++ << " ";
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
		test2.push_back(i);
	it1 = test2.begin();
	it2 = test2.end();
	std::cout << "test2 : ";
	while (it1 != it2)
		std::cout << *it1++ << " ";
	std::cout << std::endl;
	test2.merge(test1);
    test2.reverse();
	it1 = test2.begin();
	it2 = test2.end();
	while (it1 != it2)
		std::cout << *it1++ << " ";
	std::cout << std::endl;
}

void test_splice()
{
    ft::list<int>lst1;
    ft::list<int>lst2;

    lst1.push_back(1);
    lst1.push_back(2);
    lst1.push_back(3);
    lst1.push_back(4);
    lst2.push_back(5);
    lst2.push_back(6);
    lst2.push_back(7);
    lst2.push_back(8);
    ft::list<int>::iterator it = lst1.begin();
    ++it;
    ft::list<int>::iterator fst = lst2.begin();
    ft::list<int>::iterator lst = lst2.end();
    lst--;
    lst1.splice(it, lst2, lst);
    for (ft::list<int>::reverse_iterator i = lst1.rbegin(); i != lst1.rend(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
    for (ft::list<int>::reverse_iterator i = lst2.rbegin(); i != lst2.rend(); ++i)
        std::cout << *i << " ";
    std::cout << std::endl;
}

int main()
{
	//test_insert();
    //test_swap();
    test_merge();
    //test_splice();
	return 0;
}