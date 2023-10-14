#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <deque>

class PmergeMe
{
    private:


    public:
    PmergeMe();
    PmergeMe(int count, char **argv);
    PmergeMe &operator=(const PmergeMe &rhs);
    ~PmergeMe();

    bool input_parsing(std::string s);
}



#endif