#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <deque>
#include <ctime>

class PmergeMe
{
    private:
        int* numbers;
        std::list<int> listContainer;
        std::deque<int> dequeContainer;
        clock_t deque_start_time;
        clock_t list_start_time;
        clock_t deque_end_time;
        clock_t list_end_time;
        int num_count;

    public:
    PmergeMe();
    PmergeMe(int count, char **argv);
    PmergeMe &operator=(const PmergeMe &rhs);
    ~PmergeMe();

    bool    input_parsing(std::string s);
    void    fill_number_array(int count, char **argv);
    void    fill_special_case(char **argv);
    void    sorting_list(int *numbers);
    void    sorting_deque(std::deque<int>& dequeContainer);
}



#endif