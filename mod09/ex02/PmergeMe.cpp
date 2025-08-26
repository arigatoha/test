#include "PmergeMe.hpp"
#include <stdlib.h>
#include <errno.h>
#include <stdexcept>
#include <iostream>
#include <utility>
#include <algorithm>

int PmergeMe::_compCount = 0;

PmergeMe::PmergeMe() {
	std::cout << "constructor";
}

PmergeMe::~PmergeMe() {
	std::cout << "destructor";
}

PmergeMe::PmergeMe(const PmergeMe &other) {
	std::cout << "copy constructor";
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
	(void)other;
	return *this;
}


std::vector<int>    PmergeMe::parseInput(int numbers_count, char **numbers) {
    std::vector<int> unsortedVec;
	
	unsortedVec.reserve(numbers_count);
	std::cout << "capacity: " << unsortedVec.capacity() << std::endl;

    for (int i = 0; i < numbers_count; ++i) {
		char *end = NULL;
        long num = std::strtol(numbers[i], &end, 10);

        if (errno != 0)
            throw std::logic_error("couldn't parse the input.");
        unsortedVec.push_back(static_cast<int>(num));
	}
	printVec(unsortedVec, UNSORTED);
	return unsortedVec;
}

void	PmergeMe::printVec(const std::vector<int> &v, bool isSorted) {
	switch(isSorted) {
		case SORTED:
			std::cout << "After:	";
			break;
		default:
			std::cout << "Before:	";
			break;
	}
	for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printVec(const std::vector<std::vector<int>::iterator> &v, bool isSorted) {
	switch(isSorted) {
		case SORTED:
			std::cout << "After:	";
			break;
		default:
			std::cout << "Before:	";
			break;
	}
	for (std::vector<std::vector<int>::iterator>::const_iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << **it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::sortVec(std::vector<int> &container, int pair_lvl) {
	typedef std::vector<int>::iterator Iterator;
	
	int pair_units = container.size() / pair_lvl;
	if (pair_units < 2)
		return;

	bool is_odd = pair_units % 2 == 1;
	
	Iterator begin = container.begin();
	Iterator last = _next(container.begin(), pair_lvl * pair_units);
	Iterator end = _next(last, -(is_odd * pair_lvl));

	int jump = 2 * pair_lvl;
	for (Iterator it = begin; it != end; std::advance(it, jump)) {
		
		Iterator this_pair = _next(it, pair_lvl - 1);
		Iterator next_pair = _next(it, pair_lvl * 2 - 1);
	
		// std::cout << "this pair:" << *this_pair << '\n';
		// std::cout << "next pair:" << *next_pair << '\n';

		if (!_comp(this_pair, next_pair)) {
			_swap_pair(this_pair, pair_lvl);		
		}
	}
	sortVec(container, pair_lvl * 2);

	std::vector<Iterator> main;
	std::vector<Iterator> pend;

	main.insert(main.begin(), _next(begin, pair_lvl - 1));
	main.insert(main.end(), _next(begin, pair_lvl * 2 - 1));

	for (int i = 4; i <= pair_units; i+=2) {
		pend.insert(pend.end(), _next(begin, pair_lvl * (i - 1) - 1));
		main.insert(main.end(), _next(begin, pair_lvl * i - 1));
	}
	if (is_odd) {
		pend.insert(pend.end(), _next(end, pair_lvl - 1));
	}
	std::cout << "before";
	printVec(pend, false);
	printVec(main, true);

	int prevJacobsthal = _JacobsthalNum(1);
	int InsertedCount = 0;
	for (int k = 2;; ++k) {
		int currJacobsthal = _JacobsthalNum(k);
		int JacobsthalDiff = currJacobsthal - prevJacobsthal;
		if (static_cast<int>(pend.size()) < JacobsthalDiff)
			break;
		int offset = 0;
		int bound = InsertedCount + currJacobsthal;
		for (int timesToInsert = JacobsthalDiff; timesToInsert; --timesToInsert) {
			int pendPos = timesToInsert - 1;
			typename std::vector<Iterator>::iterator InsertPos = 
				std::upper_bound(main.begin(), _next(main.begin(), bound), pend.at(pendPos), _comp<Iterator>);
			
			std::vector<Iterator>::iterator inserted = main.insert(InsertPos, pend.at(pendPos));
			pend.erase(_next(pend.begin(), pendPos));

			offset += inserted == _next(main.begin(), InsertedCount + currJacobsthal);
			bound = InsertedCount + currJacobsthal - offset;
		}
		prevJacobsthal = currJacobsthal;
		InsertedCount += JacobsthalDiff;
	}
	std::cout << "after:";
	printVec(pend, false);
	printVec(main, true);
	std::cout << _compCount << std::endl;
}

