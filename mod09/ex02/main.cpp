#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "minimum 2 numbers required to sort";
    }
	
    PmergeMe    vecSort;
    
    std::vector<int> v = vecSort.parseInput(argc - 1, ++argv);

    vecSort.sortVec(v, 1);

    vecSort.printVec(v, SORTED);

    int step = 1;
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        if (it == v.end() || PmergeMe::_comp(it, PmergeMe::_next(it, step)))
            return -1;
    }
}
