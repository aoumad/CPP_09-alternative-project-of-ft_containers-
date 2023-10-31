#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int count, char **argv)
{
    std::string s;
    numbers = std::vector<int>(1e7);
    nbr_length = 0;
    num_count = 0;

    if (count < 2)
    {
        std::cerr << "Error: Not enough arguments." << std::endl;
        exit(1);
    }
    else
    {
        for (int i = 1; i < count; i++)
        {
            s = argv[i];
            if (input_parsing(s) == false)
                exit(1);
        }
        std::cout << "Before: ";
        for (int i = 1; i < count; i++)
            std::cout << argv[i] << " ";
        std::cout << std::endl;
    }
    listContainer = std::list<int>(nbr_length + 5);
    listContainer.clear();
    list_start_time = clock();

    for (int i = 0; i < nbr_length; i++)
        listContainer.push_back(numbers[i]);

    sorting_list();
    list_end_time = clock();
    std::cout << "After: ";
    for (std::list<int>::iterator it = listContainer.begin(); it != listContainer.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;


    // deque Container sorting
    deque_start_time = clock();
    for (int i = 0; i < nbr_length; i++)
        dequeContainer.push_back(numbers[i]);
    sorting_deque();
    deque_end_time = clock();
    // std::cout << "After: ";
    // for (std::deque<int>::iterator it = dequeContainer.begin(); it != dequeContainer.end(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;
    std::cout << "Time to process a range of " << nbr_length << " elements with std::list: " << (float)(list_end_time - list_start_time)/ CLOCKS_PER_SEC << " sec" << std::endl;
    std::cout << "Time to process a range of " << nbr_length << " elements with std::deque: " << (float)(deque_end_time - deque_start_time)/ CLOCKS_PER_SEC << " sec" << std::endl;
}

PmergeMe::~PmergeMe()
{
}


bool    PmergeMe::input_parsing(std::string s)
{
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    long num;
    // check if the string has a space and contains multiple numbers inside it
    if (s.find(delimiter) != std::string::npos)
    {
        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            if (input_parsing(token) == false)
                return (false);
            s.erase(0, pos + delimiter.length());
        }
        token = s.substr(0, pos);
        if (input_parsing(token) == false)
            return (false);
        return (true);
    }

    if (s.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cerr << "Error: non numeric arguments" << std::endl;
        return (false);
    }
    // get the length of the string
    int len = s.length();
    if (len > 10 && s.find_first_not_of(" ") != std::string::npos)
    {
        std::cerr << "Error: the number is too long" << std::endl;
        return (false);
    }

    std::istringstream(s) >> num;

    if (std::istringstream(s).fail() || num >= INT_MAX)
    {
        std::cerr << "Error: Out-of-range number: " << num << std::endl;
        return (false);
    }
    
    if (num < 0)
    {
        std::cerr << "Error: negative number: " << num << std::endl;
        return (false);
    }

    numbers[nbr_length] = (int)num;
    nbr_length++;
    return (true);
}



void    PmergeMe::sorting_list()
{
    size_t size = listContainer.size();
    std::list<std::pair<int, int> > pair_container;
    int struggler = -1;

    if (size < 2)
        return ; // nothing to sort;

    int div = size / 2;
    int i = 0;
    std::list<int>::iterator it = listContainer.begin();
    while (div > 0)
    {
        pair_container.push_back(std::make_pair(*it, *(++it)));
        div--;
        i += 2;
        it++;
    }
    if (size % 2 != 0)
    {
        std::list<int>::iterator it_struggler = listContainer.end();
        it_struggler--;
        struggler = *it_struggler;
        std::cout << "struggler: " << struggler << std::endl;
    }
    int first = 0;
    int second = 0;
    std::list<std::pair<int, int> >::iterator it_pair = pair_container.begin();
    for (std::list<std::pair<int, int> >::size_type k = 0; k < pair_container.size(); ++k)
    {
        first = it_pair->first;   // lkbir 3ad sghir
        second = it_pair->second;
        if (first - second < 0 )
        {
            first = first + second;
            second = first - second;
            first = first - second;
        }
        it_pair->first = first;
        it_pair->second = second;
        it_pair++;
    }
    // // Sort the pair_container based on their first number using insertion sort
    std::list<std::pair<int, int> >::iterator ites = pair_container.begin();
    for (; ites != pair_container.end(); ++ites)
    {
        int first_num = ites->first;
        int second_num = ites->second;
        std::list<std::pair<int, int> >::iterator insertion_point = ites;
        
        // Find the correct position for the current pair
        while (insertion_point != pair_container.begin())
        {
            std::list<std::pair<int, int> >::iterator prev = insertion_point;
            --prev;

            if (first_num < prev->first)
            {
                // Swap the elements
                insertion_point->first = prev->first;
                insertion_point->second = prev->second;
                --insertion_point; // Move the insertion point to the left
            }
            else
            {
                break;
            }
        }

        // Insert the current pair at the correct position
        insertion_point->first = first_num;
        insertion_point->second = second_num;
    }

    // split the pairs into main chain and pend chain
    std::list<int> first_chain;
    std::list<int> second_chain;
    std::list<std::pair<int, int> >::iterator it_chains = pair_container.begin();
    for (; it_chains != pair_container.end(); ++it_chains)
    {
        first_chain.push_back(it_chains->first);
        second_chain.push_back(it_chains->second);
    }

    size_t second_chain_size = second_chain.size();
    size_t a = 1;
    size_t starting_index = 3;
    size_t rtn_jcb;
    for (size_t i = 0; i < second_chain_size - 1; i++)
    {
        rtn_jcb = get_jcb_nbr(starting_index);
        jacobsthal_list.push_back(rtn_jcb);
    
        while (rtn_jcb > 2)
        {
            rtn_jcb--;
            if (std::find(jacobsthal_list.begin(), jacobsthal_list.end(), rtn_jcb) == jacobsthal_list.end())
                jacobsthal_list.push_back(rtn_jcb);
            if (++a >= (second_chain_size * 2))
                break;
        }
        starting_index++;
        if (a >= (second_chain_size * 2))
            break;
    }
    insert_second_chain(first_chain, second_chain);

    if (struggler != -1)
    {
        std::list<int>::iterator it_first_chain = first_chain.begin();
        while (it_first_chain != first_chain.end())
        {
            if (*it_first_chain > struggler)
            {
                first_chain.insert(it_first_chain, struggler);
                break;
            }
            ++it_first_chain;
        }
    }
    listContainer.clear();
    listContainer = first_chain;
}

size_t  PmergeMe::get_jcb_nbr(int index)
{
    if (index == 0)
        return (0);

    if (index == 1)
        return (1);

    return (get_jcb_nbr(index - 1) + 2 * get_jcb_nbr(index - 2));
}

void PmergeMe::insert_second_chain(std::list<int> &first_chain, std::list<int> &second_chain)
{
    std::list<int> jacobsthal_list_copy = jacobsthal_list;
    std::list<int>::iterator it_jcb = jacobsthal_list_copy.begin();
    std::vector<bool> second_chain_inserted(second_chain.size(), false);
    std::list<int>::iterator it_second_chain;
    std::list<int>::iterator it_first_chain;

    while (it_jcb != jacobsthal_list_copy.end())
    {
        size_t jcb_element = *it_jcb - 1;

        it_second_chain = second_chain.begin();
        for (size_t i = 0; i < jcb_element; ++i)
        {
            ++it_second_chain;
            if (it_second_chain == second_chain.end())
                it_second_chain = second_chain.begin();
        }
        it_first_chain = first_chain.begin();
        while (it_first_chain != first_chain.end())
        {
            if (second_chain_inserted[jcb_element % second_chain.size()] == true)
                break;
            if (*it_first_chain > *it_second_chain)
            {
                first_chain.insert(it_first_chain, *it_second_chain);
                second_chain_inserted[jcb_element % second_chain.size()] = true;
                break;
            }
            ++it_first_chain;
        }
        ++it_jcb;
    }
}

void    PmergeMe::sorting_deque()
{
    size_t size = dequeContainer.size();
    std::deque<std::pair<int, int> > pair_container;
    int struggler = -1;

    if (size < 2)
        return ; // nothing to sort
    
    int div = size / 2;
    int i = 0;
    std::deque<int>::iterator it = dequeContainer.begin();
    while (div > 0)
    {
        pair_container.push_back(std::make_pair(*it, *(++it)));
        div--;
        i += 2;
        it++;
    }

    if (size % 2 != 0)
    {
        std::deque<int>::iterator it_struggler = dequeContainer.end();
        it_struggler--;
        struggler = *it_struggler;
    }
    int first = 0;
    int second = 0;
    std::deque<std::pair<int, int> >::iterator it_pair = pair_container.begin();
    for (std::deque<std::pair<int, int> >::size_type k = 0; k < pair_container.size(); ++k)
    {
        first = it_pair->first;
        second = it_pair->second;
        if (first - second < 0 )
        {
            first = first + second;
            second = first - second;
            first = first - second;
        }
        it_pair->first = first;
        it_pair->second = second;
        it_pair++;
    }
    
    // // Sort the pair_container based on their first number using insertion sort
    for (int i = 0; i < (int)pair_container.size(); ++i)
    {
        int first_num = pair_container[i].first;
        int second_num = pair_container[i].second;
        int insertion_point = i;

        // find the correct position for the current pair
        while (insertion_point > 0 && first_num < (int)pair_container[insertion_point - 1].first)
        {
            // Swap the elements
            pair_container[insertion_point].first = pair_container[insertion_point - 1].first;
            pair_container[insertion_point].second = pair_container[insertion_point - 1].second;
            --insertion_point; // Move the insertion point to the left
        }

        // Insert the current pair at the correct position
        pair_container[insertion_point].first = first_num;
        pair_container[insertion_point].second = second_num;
    }
    // split the pairs into main chain and pend chain
    std::deque<int> first_chain;
    std::deque<int> second_chain;
    for (size_t i = 0; i < (size_t)pair_container.size(); i++)
    {
        first_chain.push_back(pair_container[i].first);
        second_chain.push_back(pair_container[i].second);
    }
    // need to implement the algo
    std::deque<int> jacobsthal_deque;
    int second_chain_size = second_chain.size();

    int a = 1;
    int b = 1;
    int c;
    int flag = 2;
    int k = 1;
    for (int i = 0; i < second_chain_size; i++)
    {
        c = b + (2 * a);
        jacobsthal_deque.push_back(c);
        for (int j = c - 1; j >= flag; j--)
        {
            if (std::find(jacobsthal_deque.begin(), jacobsthal_deque.end(), j) == jacobsthal_deque.end())
                jacobsthal_deque.push_back(j);
            if (++k >= second_chain_size * 2)
                break;
        }
        a = b;
        b = c;
        flag = c;
        if (k >= second_chain_size * 2)
            break;
    }

    insert_second_chain_deque(first_chain, second_chain, jacobsthal_deque);
    if (struggler != -1)
    {
        std::deque<int>::iterator it_first_chain = first_chain.begin();
        while (it_first_chain != first_chain.end())
        {
            if (*it_first_chain > struggler)
            {
                first_chain.insert(it_first_chain, struggler);
                break;
            }
            ++it_first_chain;
        }
    }
    dequeContainer.clear();
    dequeContainer = first_chain;
}

void PmergeMe::insert_second_chain_deque(std::deque<int> &first_chain, std::deque<int> &second_chain, std::deque<int> &jacobsthal_deque)
{
    std::deque<int> dp(second_chain.size(), false);

    if (second_chain.empty() || jacobsthal_deque.empty())
        return ;

    std::deque<int>::iterator it_jcb = jacobsthal_deque.begin();
    std::deque<int>::iterator it_second_chain;
    std::deque<int>::iterator it_first_chain;
    int jcb_element;

    while (it_jcb != jacobsthal_deque.end())
    {
        jcb_element = *it_jcb - 1;
        it_second_chain = second_chain.begin();

        for (int i = 0; i < jcb_element; i++)
        {
            ++it_second_chain;
            if (it_second_chain == second_chain.end())
                it_second_chain = second_chain.begin();
        }

        it_first_chain = first_chain.begin();

        while (it_first_chain != first_chain.end())
        {
            if (dp[jcb_element % second_chain.size()] == true)
                break;
            if (*it_first_chain > *it_second_chain)
            {
                first_chain.insert(it_first_chain, *it_second_chain);
                dp[jcb_element % second_chain.size()] = true;
                break;
            }
            ++it_first_chain;
        }
        ++it_jcb;
    }
}