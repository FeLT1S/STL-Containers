/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiandre <jiandre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:12:12 by gmoshe            #+#    #+#             */
/*   Updated: 2021/06/12 18:49:33 by jiandre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <vector>
#include "List.hpp"

void test_constructs()
{
	std::cout << " TEST CONSTRUCTS \n\n";

	std::list<int> test_std1;
	std::cout << "std default:           " <<*test_std1.begin() << std::endl;
	
	std::list<int> test_std2(5, 10);
	std::list<int>::iterator it_std1 = test_std2.begin();
	std::cout << "std list(5, 10):       ";
	while(it_std1 != test_std2.end())
		std::cout << *it_std1++ << " ";
	std::cout << std::endl;

	std::list<int> test_std3(test_std2);
	std::list<int>::iterator it_std2 = test_std3.begin();
	std::cout << "std constructor copy:  ";
	while(it_std2 != test_std3.end())
		std::cout << *it_std2++ << " ";
	std::cout << std::endl;

	std::list<int> test_std4(test_std3.begin(), test_std3.end());
	std::list<int>::iterator it_std3 = test_std4.begin();
	std::cout << "std list(first, last): ";
	while(it_std3 != test_std4.end())
		std::cout << *it_std3++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	ft::list<int> test_ft1;
	std::cout << "my default:           " <<*test_std1.begin() << std::endl;
	
	ft::list<int> test_ft2(5, 10);
	ft::list<int>::iterator it_ft1 = test_ft2.begin();
	std::cout << "my list(5, 10):       ";
	while(it_ft1 != test_ft2.end())
		std::cout << *it_ft1++ << " ";
	std::cout << std::endl;

	ft::list<int> test_ft3(test_ft2);
	ft::list<int>::iterator it_ft2 = test_ft3.begin();
	std::cout << "my constructor copy:  ";
	while(it_ft2 != test_ft3.end())
		std::cout << *it_ft2++ << " ";
	std::cout << std::endl;

	ft::list<int> test_ft4(test_ft3.begin(), test_ft3.end());
	ft::list<int>::iterator it_ft3 = test_ft4.begin();
	std::cout << "my list(first, last): ";
	while(it_ft3 != test_ft4.end())
		std::cout << *it_ft3++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_push_pop()
{
	std::cout << "PUSH_BACK PUSH_FRONT POP_BACK POP_FRONT\n\n";
	
	std::list<int> test_std1(5, 4);
	ft::list<int> test_ft1(5, 4);
	
	std::list<int>::iterator it_std = test_std1.begin();
	ft::list<int>::iterator it_ft = test_ft1.begin();
	std::cout << "std list: ";
	while (it_std != test_std1.end())
		std::cout << *it_std++ << " ";
	std::cout << "\nft  list: ";
	while (it_ft != test_ft1.end())
		std::cout << *it_ft++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << "PUSH_BACK\n";
	test_std1.push_back(10);
	test_std1.push_back(10);
	test_ft1.push_back(10);
	test_ft1.push_back(10);
	std::cout << "std: ";
	it_std = test_std1.begin();
	it_ft = test_ft1.begin();
	while (it_std != test_std1.end())
		std::cout << *it_std++ << " ";
	std::cout << "\nft:  ";
	while (it_ft != test_ft1.end())
		std::cout << *it_ft++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	
	std::cout << "PUSH_FRONT\n";
	test_std1.push_front(5);
	test_std1.push_front(5);
	test_ft1.push_front(5);
	test_ft1.push_front(5);
	std::cout << "std: ";
	it_std = test_std1.begin();
	it_ft = test_ft1.begin();
	while (it_std != test_std1.end())
		std::cout << *it_std++ << " ";
	std::cout << "\nft:  ";
	while (it_ft != test_ft1.end())
		std::cout << *it_ft++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "POP_BACK\n";
	test_std1.pop_back();
	test_ft1.pop_back();
	std::cout << "std: ";
	it_std = test_std1.begin();
	it_ft = test_ft1.begin();
	while (it_std != test_std1.end())
		std::cout << *it_std++ << " ";
	std::cout << "\nft:  ";
	while (it_ft != test_ft1.end())
		std::cout << *it_ft++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "POP_FRONT\n";
	test_std1.pop_front();
	test_ft1.pop_front();
	std::cout << "std: ";
	it_std = test_std1.begin();
	it_ft = test_ft1.begin();
	while (it_std != test_std1.end())
		std::cout << *it_std++ << " ";
	std::cout << "\nft:  ";
	while (it_ft != test_ft1.end())
		std::cout << *it_ft++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_insert()
{
	std::cout << "INSERT\n\n";

	std::list<int> std_test1(5, 11);
	ft::list<int> ft_test1(5, 11);
	std::list<int> std_test2(4, 2);
	ft::list<int> ft_test2(4, 2);

	std::list<int>::iterator std_it = std_test1.begin();
	ft::list<int>::iterator ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.insert(++std_test1.begin(), 10);
	ft_test1.insert(++ft_test1.begin(), 10);
	
	std_it = std_test1.begin();
	ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.insert(std_test1.begin(), 3, 3);
	ft_test1.insert(ft_test1.begin(), 3, 3);
	
	std_it = std_test1.begin();
	ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.insert(std_test1.end(), std_test2.begin(), std_test2.end());
	ft_test1.insert(ft_test1.end(), ft_test2.begin(), ft_test2.end());
	
	std_it = std_test1.begin();
	ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_erase()
{
	std::cout << "ERASE\n\n";
	
	std::list<int> std_test1;
	ft::list<int> ft_test1;

	for (int i = 0; i < 8; i++)
		std_test1.push_back(i);
	for (int i = 0; i < 8; i++)
		ft_test1.push_back(i);

	std::list<int>::iterator std_it = std_test1.begin();
	ft::list<int>::iterator ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.erase(std_test1.begin());
	ft_test1.erase(ft_test1.begin());
	std_test1.erase(--std_test1.end());
	ft_test1.erase(--ft_test1.end());
	std_test1.erase(++std_test1.begin());
	ft_test1.erase(++ft_test1.begin());
	
	std_it = std_test1.begin();
	ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.erase(++std_test1.begin(), --std_test1.end());
	ft_test1.erase(++ft_test1.begin(), --ft_test1.end());
	
	std_it = std_test1.begin();
	ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_clear()
{
	std::cout << "ERASE\n\n";
	
	std::list<int> std_test1(5, 10);
	ft::list<int> ft_test1(5, 10);
	
	std::list<int>::iterator std_it = std_test1.begin();
	ft::list<int>::iterator ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << "\nstd size: " << std_test1.size();
	std::cout << "\nft size:  " << std_test1.size();
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.clear();
	ft_test1.clear();
	std_it = std_test1.begin();
	ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << "\nstd size: " << std_test1.size();
	std::cout << "\nft size:  " << std_test1.size();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_resize()
{
	std::cout << "RESIZE\n\n";

	std::list<int> std_test1(5, 10);
	ft::list<int> ft_test1(5, 10);
	std::list<int>::iterator std_it = std_test1.begin();
	ft::list<int>::iterator ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.resize(3, 5);
	ft_test1.resize(3, 5);
	std_it = std_test1.begin();
	ft_it = ft_test1.begin();
	std::cout << "std list: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << "\nft  list: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_swap()
{
	std::cout << "SWAP\n\n";

	std::list<int> std_test1(5, 8);
	std::list<int> std_test2(5, 9);

	std::list<int>::iterator std_it = std_test1.begin();
	std::list<int>::iterator std_it2 = std_test2.begin();
	std::cout << "std list1: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "std list2: ";
	while (std_it2 != std_test2.end())
		std::cout << *std_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	
	std_test1.swap(std_test2);
	std_it = std_test1.begin();
	std_it2 = std_test2.begin();
	std::cout << "std list1: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "std list2: ";
	while (std_it2 != std_test2.end())
		std::cout << *std_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	ft::list<int> ft_test1(5, 8);
	ft::list<int> ft_test2(5, 9);

	ft::list<int>::iterator ft_it = ft_test1.begin();
	ft::list<int>::iterator ft_it2 = ft_test2.begin();
	std::cout << "ft list1: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list2: ";
	while (ft_it2 != ft_test2.end())
		std::cout << *ft_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	
	ft_test1.swap(ft_test2);
	ft_it = ft_test1.begin();
	ft_it2 = ft_test2.begin();
	std::cout << "ft list1: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list2: ";
	while (ft_it2 != ft_test2.end())
		std::cout << *ft_it2++ << " ";

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_reverse()
{
	std::cout << "REVERSE\n\n";

	std::list<int> std_test;
	ft::list<int> ft_test;
	
	for (int i = 1; i < 11; i++)
		std_test.push_back(i);
	for (int i = 1; i < 11; i++)
		ft_test.push_back(i);
	std::list<int>::iterator std_it = std_test.begin();
	ft::list<int>::iterator ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	
	std_test.reverse();
	ft_test.reverse();
	std_it = std_test.begin();
	ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_assign()
{
	std::cout << "REVERSE\n\n";

	std::list<int> std_test;
	ft::list<int> ft_test;
	std::list<int> std_test2(5, 20);
	ft::list<int> ft_test2(5, 20);
	
	for (int i = 1; i < 11; i++)
		std_test.push_back(i);
	for (int i = 1; i < 11; i++)
		ft_test.push_back(i);
	std::list<int>::iterator std_it = std_test.begin();
	ft::list<int>::iterator ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	
	std_test.assign(3, 10);
	ft_test.assign(3, 10);
	std_it = std_test.begin();
	ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test.assign(std_test2.begin(), std_test2.end());
	ft_test.assign(ft_test2.begin(), ft_test2.end());
	std_it = std_test.begin();
	ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_sort()
{
	std::cout << "SORT\n\n";

	std::list<int> std_test;
	ft::list<int> ft_test;

	for (int i = 1; i < 11; i += 2)
		std_test.push_back(i);
	for (int i = 2; i < 11; i += 2)
		std_test.push_back(i);
	for (int i = 1; i < 11; i += 2)
		ft_test.push_back(i);
	for (int i = 2; i < 11; i += 2)
		ft_test.push_back(i);
	
	std::list<int>::iterator std_it = std_test.begin();
	ft::list<int>::iterator ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test.sort();
	ft_test.sort();
	std_it = std_test.begin();
	ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

template<typename Type>
struct mer
{
bool operator()(const Type &a, const Type &b) {return a > b;}
};

void test_merge()
{
	std::cout << "MERGE\n\n";

	std::list<int> std_test1;
	std::list<int> std_test2;

	for (int i = 1; i < 11; i++)
		std_test1.push_back(i);
	for (int i = 1; i < 11; i++)
		std_test2.push_back(i);

	std::list<int>::iterator std_it = std_test1.begin();
	std::list<int>::iterator std_it2 = std_test2.begin();
	std::cout << "std list1: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "std list2: ";
	while (std_it2 != std_test2.end())
		std::cout << *std_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.merge(std_test2);
	std_it = std_test1.begin();
	std_it2 = std_test2.begin();
	std::cout << "std list1: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "std list2: ";
	while (std_it2 != std_test2.end())
		std::cout << *std_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	ft::list<int> ft_test1;
	ft::list<int> ft_test2;

	for (int i = 1; i < 11; i++)
		ft_test1.push_back(i);
	for (int i = 1; i < 11; i++)
		ft_test2.push_back(i);

	ft::list<int>::iterator ft_it = ft_test1.begin();
	ft::list<int>::iterator ft_it2 = ft_test2.begin();
	std::cout << "ft list1: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list2: ";
	while (ft_it2 != ft_test2.end())
		std::cout << *ft_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	ft_test1.merge(ft_test2);
	ft_it = ft_test1.begin();
	ft_it2 = ft_test2.begin();
	std::cout << "ft list1: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list2: ";
	while (ft_it2 != ft_test2.end())
		std::cout << *ft_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;//дописать с принимаемым компоратором
}

template<typename Type>
struct pred
{
bool operator()(const Type &a, const Type &b) {return a == b;}
};

void test_unique()
{
	std::cout << "UNIQUE\n\n";

	std::list<int> std_test;
	ft::list<int> ft_test;

	for (int i = 1; i < 5; i++)
	{
		std_test.push_back(i);
		std_test.push_back(i);
	}
	for (int i = 1; i < 5; i++)
	{
		std_test.push_back(i);
		std_test.push_back(i);
	}
	for (int i = 1; i < 5; i++)
	{
		ft_test.push_back(i);
		ft_test.push_back(i);
	}
	for (int i = 1; i < 5; i++)
	{
		ft_test.push_back(i);
		ft_test.push_back(i);
	}
	
	std::list<int>::iterator std_it = std_test.begin();
	ft::list<int>::iterator ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test.unique();
	ft_test.unique();
	std_it = std_test.begin();
	ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_unique_comp()
{
	std::cout << "UNIQUE(comp)\n\n";

	std::list<int> std_test;
	ft::list<int> ft_test;

	for (int i = 1; i < 5; i++)
	{
		std_test.push_back(i);
		std_test.push_back(i);
	}
	for (int i = 1; i < 5; i++)
	{
		std_test.push_back(i);
		std_test.push_back(i);
	}
	for (int i = 1; i < 5; i++)
	{
		ft_test.push_back(i);
		ft_test.push_back(i);
	}
	for (int i = 1; i < 5; i++)
	{
		ft_test.push_back(i);
		ft_test.push_back(i);
	}
	
	std::list<int>::iterator std_it = std_test.begin();
	ft::list<int>::iterator ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test.unique(pred<int>());
	ft_test.unique(pred<int>());
	std_it = std_test.begin();
	ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_remove()
{
	std::cout << "REMOVE\n\n";

	std::list<int> std_test;
	ft::list<int> ft_test;

	for (int i = 2; i < 11; i++)
	{
		std_test.push_back(1);
		std_test.push_back(i);
	}
	for (int i = 2; i < 11; i++)
	{
		ft_test.push_back(1);
		ft_test.push_back(i);
	}
	
	std::list<int>::iterator std_it = std_test.begin();
	ft::list<int>::iterator ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test.remove(1);
	ft_test.remove(1);
	std_it = std_test.begin();
	ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

bool comp(const int &value)
{
	if (value == 1)
		return true;
	return false;
}

void test_remove_if()
{
	std::cout << "REMOVE_IF\n\n";

	std::list<int> std_test;
	ft::list<int> ft_test;

	for (int i = 2; i < 11; i++)
	{
		std_test.push_back(1);
		std_test.push_back(i);
	}
	for (int i = 2; i < 11; i++)
	{
		ft_test.push_back(1);
		ft_test.push_back(i);
	}
	
	std::list<int>::iterator std_it = std_test.begin();
	ft::list<int>::iterator ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test.remove_if(comp);
	ft_test.remove_if(comp);
	std_it = std_test.begin();
	ft_it = ft_test.begin();
	std::cout << "std list: ";
	while (std_it != std_test.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << "ft list:  ";
	while (ft_it != ft_test.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "***********************************************";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_splice()
{
	std::cout << "SPLICE\n\n";

	std::list<int> std_test1(2, 44);
	std::list<int> std_test2;
	ft::list<int> ft_test1(2, 44);
	ft::list<int> ft_test2;

	for (int i = 1; i < 11; i++)
		std_test2.push_back(i);
	for (int i = 1; i < 11; i++)
		ft_test2.push_back(i);
	
	std::list<int>::iterator std_it1 = std_test1.begin();
	std::list<int>::iterator std_it2 = std_test2.begin();
	ft::list<int>::iterator ft_it1 = ft_test1.begin();
	ft::list<int>::iterator ft_it2 = ft_test2.begin();
	std::cout << "std list1: ";
	while (std_it1 != std_test1.end())
		std::cout << *std_it1++ << " ";
	std::cout << std::endl;
	std::cout << "std list2: ";
	while (std_it2 != std_test2.end())
		std::cout << *std_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "ft list1 :  ";
	while (ft_it1 != ft_test1.end())
		std::cout << *ft_it1++ << " ";
	std::cout << std::endl;
	std::cout << "ft list2 :  ";
	while (ft_it2 != ft_test2.end())
		std::cout << *ft_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test1.splice(std_test1.begin(), std_test2);
	ft_test1.splice(ft_test1.begin(), ft_test2);
	std_it1 = std_test1.begin();
	std_it2 = std_test2.begin();
	ft_it1 = ft_test1.begin();
	ft_it2 = ft_test2.begin();
	std::cout << "std list1: ";
	while (std_it1 != std_test1.end())
		std::cout << *std_it1++ << " ";
	std::cout << std::endl;
	std::cout << "std list2: ";
	while (std_it2 != std_test2.end())
		std::cout << *std_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "ft list1 :  ";
	while (ft_it1 != ft_test1.end())
		std::cout << *ft_it1++ << " ";
	std::cout << std::endl;
	std::cout << "ft list2 :  ";
	while (ft_it2 != ft_test2.end())
		std::cout << *ft_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test2.splice(std_test2.begin(), std_test1, std_test1.begin());
	ft_test2.splice(ft_test2.begin(), ft_test1, ft_test1.begin());//проблема при удалении из конца списка
	std_it1 = std_test1.begin();
	std_it2 = std_test2.begin();
	ft_it1 = ft_test1.begin();
	ft_it2 = ft_test2.begin();
	std::cout << "std list1: ";
	while (std_it1 != std_test1.end())
		std::cout << *std_it1++ << " ";
	std::cout << std::endl;
	std::cout << "std list2: ";
	while (std_it2 != std_test2.end())
		std::cout << *std_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "ft list1 :  ";
	while (ft_it1 != ft_test1.end())
		std::cout << *ft_it1++ << " ";
	std::cout << std::endl;
	std::cout << "ft list2 :  ";
	while (ft_it2 != ft_test2.end())
		std::cout << *ft_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;

	std_test2.splice(std_test2.begin(), std_test1, ++std_test1.begin(), --std_test1.end());
	ft_test2.splice(ft_test2.begin(), ft_test1, ++ft_test1.begin(), --ft_test1.end());
	std_it1 = std_test1.begin();
	std_it2 = std_test2.begin();
	ft_it1 = ft_test1.begin();
	ft_it2 = ft_test2.begin();
	std::cout << "std list1: ";
	while (std_it1 != std_test1.end())
		std::cout << *std_it1++ << " ";
	std::cout << std::endl;
	std::cout << "std list2: ";
	while (std_it2 != std_test2.end())
		std::cout << *std_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "ft list1 :  ";
	while (ft_it1 != ft_test1.end())
		std::cout << *ft_it1++ << " ";
	std::cout << std::endl;
	std::cout << "ft list2 :  ";
	while (ft_it2 != ft_test2.end())
		std::cout << *ft_it2++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_operators()
{
	std::cout << "OPERATORS\n\n";

	std::list<int> std_test1(5, 10);
	std::list<int> std_test2(5, 10);

	std::list<int>::iterator std_it = std_test1.begin();
	std::cout << "std list1: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std_it = std_test2.begin();
	std::cout << "std list2: ";
	while (std_it != std_test2.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "std_list1 == std_list2: " << (std_test1 == std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 != std_list2: " << (std_test1 != std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 <  std_list2: " << (std_test1 < std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 <= std_list2: " << (std_test1 <= std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 >  std_list2: " << (std_test1 > std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 >= std_list2: " << (std_test1 >= std_test2);
	std::cout << std::endl;
	std::cout << std::endl;
	
	std_test2.pop_back();
	std_it = std_test1.begin();
	std::cout << "std list1: ";
	while (std_it != std_test1.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std_it = std_test2.begin();
	std::cout << "std list2: ";
	while (std_it != std_test2.end())
		std::cout << *std_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "std_list1 == std_list2: " << (std_test1 == std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 != std_list2: " << (std_test1 != std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 <  std_list2: " << (std_test1 < std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 <= std_list2: " << (std_test1 <= std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 >  std_list2: " << (std_test1 > std_test2);
	std::cout << std::endl;
	std::cout << "std_list1 >= std_list2: " << (std_test1 >= std_test2);
	std::cout << std::endl;
	std::cout << std::endl;

	ft::list<int> ft_test1(5, 10);
	ft::list<int> ft_test2(5, 10);

	ft::list<int>::iterator ft_it = ft_test1.begin();
	std::cout << "ft list1: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	ft_it = ft_test2.begin();
	std::cout << "ft list2: ";
	while (ft_it != ft_test2.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "ft_list1 == ft_list2: " << (ft_test1 == ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 != ft_list2: " << (ft_test1 != ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 <  ft_list2: " << (ft_test1 < ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 <= ft_list2: " << (ft_test1 <= ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 >  ft_list2: " << (ft_test1 > ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 >= ft_list2: " << (ft_test1 >= ft_test2);
	std::cout << std::endl;
	std::cout << std::endl;
	
	ft_test2.pop_back();
	ft_it = ft_test1.begin();
	std::cout << "ft list1: ";
	while (ft_it != ft_test1.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	ft_it = ft_test2.begin();
	std::cout << "ft list2: ";
	while (ft_it != ft_test2.end())
		std::cout << *ft_it++ << " ";
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "ft_list1 == ft_list2: " << (ft_test1 == ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 != ft_list2: " << (ft_test1 != ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 <  ft_list2: " << (ft_test1 < ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 <= ft_list2: " << (ft_test1 <= ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 >  ft_list2: " << (ft_test1 > ft_test2);
	std::cout << std::endl;
	std::cout << "ft_list1 >= ft_list2: " << (ft_test1 >= ft_test2);
	std::cout << std::endl;
	std::cout << std::endl;
}

void test_base()
{
	std::cout << "TEST BASE" << std::endl;
	std::cout << std::endl;

	ft::list<int> v;

	for (unsigned long i = 0; i < 6; i++)
		v.push_back(i);

    ft::list<int>::iterator it = ++++++v.begin();
    ft::list<int>::reverse_iterator r_it = ------v.rend();
 
    std::cout << "*it == " << *it << ", *r_it.base() == " << *r_it.base()
    << '\n' << "*r_it == " << *r_it <<", *(r_it.base()-1) == " << *(--r_it.base()) << "\n";
	std::cout << std::endl;

	std::list<int> v1;

	for (unsigned long i = 0; i < 6; i++)
		v1.push_back(i);

    std::list<int>::iterator it1 = ++++++v1.begin();
    std::list<int>::reverse_iterator r_it1 = ------v1.rend();
 
    std::cout << "*it == " << *it1 << ", *r_it.base() == " << *r_it1.base()
    << '\n' << "*r_it == " << *r_it1 <<", *(r_it.base()-1) == " << *(--r_it1.base()) << "\n";
  
//   {
//     RevIt r_end(v.begin());
//     RevIt r_begin(v.end());
 
//     for (auto it = r_end.base(); it != r_begin.base(); ++it) {
//       std::cout << *it << " ";
//     }
//     std::cout << "\n";
//   }
	std::cout << std::endl;

	ft::list<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);

	typedef ft::list<int>::iterator iter_type;

	ft::list<int>::reverse_iterator rev_end (myvector.begin());
	ft::list<int>::reverse_iterator rev_begin (myvector.end());

	std::cout << "myvector:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::list<int> myvector1;
	for (int i=0; i<10; i++) myvector1.push_back(i);

	typedef std::list<int>::iterator iter_type1;

	std::reverse_iterator<iter_type1> rev_end1 (myvector1.begin());
	std::reverse_iterator<iter_type1> rev_begin1 (myvector1.end());

	std::cout << "myvector:";
	for (iter_type1 it = rev_end1.base(); it != rev_begin1.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "*******************************" << std::endl;
	std::cout << std::endl;
}

void dtring_my()
{
	// ft::list<std::vector<int> > test1;
	// std::vector<int> test2;
	// test2.push_back(1);
	// test2.push_back(2);
	// test1.push_back(test2);
	// ft::list<std::vector<int> >::iterator it = test1.begin();
	// std::cout << it->element[0] << it->element[1] << "\n";
}
int main()
{
	test_constructs();
	test_push_pop();
	test_insert();
	test_erase();
	test_clear();
	test_resize();
	test_swap();
	test_reverse();
	test_assign();
	test_sort();
	test_merge();
	test_unique();
	test_unique_comp();
	test_remove();
	test_remove_if();
	test_splice();
	test_base();
	test_operators();
}