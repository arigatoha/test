#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#define SORTED 1
#define UNSORTED 0

class PmergeMe {
    private:

        static int		_averageComplextity(int n) {
		    int sum = 0;
		    for (int k = 1; k <= n; ++k) {
		        double value = (3.0 / 4.0) * k;
		        sum += static_cast<int>(ceil(log2(value)));
		    }
		    return sum;
		} 

        bool    _isSorted(const std::vector<int> &v) {
            for(std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
                if (PmergeMe::_next(it, 1) == v.end())
                    break;
                else if (!PmergeMe::_comp(it, PmergeMe::_next(it, 1)))
                    return -1;
            }
        }

        template <typename T> static  bool    _comp(const T &a, const T &b) {
            ++_compCount;
            return *a < *b;
        }

        template <typename T> static  T    _next(T it, int steps) {
            std::advance(it, steps);

            return it;
        }

        template <typename T> static  void    _swap_pair(T &it, int pair_lvl) {
            T   start = _next(it, -(pair_lvl - 1));
            T   end = _next(start, pair_lvl);

            for (;start != end; ++start) {
                std::iter_swap(start, _next(start, pair_lvl));
            }
        }

        int     _JacobsthalNum(int n) { return (pow(2, n + 1) + pow(-1, n)) / 3; }

        void	printVec(const std::vector<int> &vec, bool isSorted);

        void	printVec(const std::vector<std::vector<int>::iterator> &v, bool isSorted);

        void	sortVec(std::vector<int> &vec, int pair_lvl);

    public:

        static int _compCount;

        PmergeMe();

        ~PmergeMe();
        
        PmergeMe(const PmergeMe &other);
        
        PmergeMe &operator=(const PmergeMe &other);
        
        void                sortInput(std::vector<int> &v);
		// handles only positive numbers
        std::vector<int>    parseInput(int numbers_count, char **numbers);

};
