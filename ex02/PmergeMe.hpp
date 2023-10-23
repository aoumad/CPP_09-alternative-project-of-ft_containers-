#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <deque>
#include <ctime>
#include <vector>

class PmergeMe
{
    private:
        std::vector<int> numbers;
        int nbr_length;
        std::list<int> listContainer;
        std::deque<int> dequeContainer;
        clock_t deque_start_time;
        clock_t list_start_time;
        clock_t deque_end_time;
        clock_t list_end_time;
        int num_count;

        std::list<int> jacobsthal_list;

    public:
    PmergeMe();
    PmergeMe(int count, char **argv);
    PmergeMe &operator=(const PmergeMe &rhs);
    ~PmergeMe();

    bool    input_parsing(std::string s, int index);
    void    sorting_list();
    void    sorting_deque();
    size_t  get_jcb_nbr(int index);
    void    insert_second_chain(std::list<int> &first_chain, std::list<int> &second_chain);
};



#endif