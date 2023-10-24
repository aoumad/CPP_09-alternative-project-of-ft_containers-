#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int count, char **argv)
{
    std::string s;
    numbers = std::vector<int>(100000);
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
    std::cout << "NUMBER LENGTH: " << nbr_length << std::endl;
    listContainer = std::list<int>(nbr_length + 5);
    listContainer.clear();
    // list Container sorting
    list_start_time = clock();
    // print the number array
    std::cout << "numbers array: ";
    for (int i = 0; i < nbr_length; i++)
        std::cout << numbers[i] << " ";
    std::cout << std::endl;
    for (int i = 0; i < nbr_length; i++)
        listContainer.push_back(numbers[i]);

        // print firstly the listContainer
    std::cout << "list container:";
    for (std::list<int>::iterator it = listContainer.begin(); it != listContainer.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    // // here i will call the template function that will sort the list
    sorting_list();
    list_end_time = clock();
    std::cout << "After: ";
    for (std::list<int>::iterator it = listContainer.begin(); it != listContainer.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << count - 1  << "elements with std::list: " << (float)(list_end_time - list_start_time) * 1000 / CLOCKS_PER_SEC << " seconds" << std::endl;

    // deque Container sorting
    deque_start_time = clock();
    for (int i = 0; i < nbr_length; i++)
        dequeContainer.push_back(numbers[i]);
    // here i will call the template function that will sort the deque
    sorting_deque();
    // deque_end_time = clock();
    // std::cout << "Time to process a range of " << count - 1  << "elements with std::deque: " << (float)(deque_end_time - deque_start_time) * 1000 / CLOCKS_PER_SEC << " seconds" << std::endl;
}

PmergeMe::~PmergeMe()
{
    // delete[] numbers;
    // delete[] jacobsthal;
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
            // nbr_length++;
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
        std::cerr << "Error: Invalid or out-of-range number: " << num << std::endl;
        return (false);
    }
    
    if (num < 0)
    {
        std::cerr << "Error" << std::endl;
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

    if (size < 2)
        return ; // nothing to sort;

    // int rem = size % 2;
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

    // priting the pairs
    // for (std::list<std::pair<int, int> >::iterator it = pair_container.begin(); it != pair_container.end(); ++it)
    //     std::cout << it->first << " " << it->second << std::endl;

    int first = 0;
    int second = 0;
    std::list<std::pair<int, int> >::iterator it_pair = pair_container.begin();
    for (std::list<std::pair<int, int> >::size_type k = 0; k < pair_container.size(); ++k)
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
    // for (std::list<std::pair<int, int> >::iterator ites = pair_container.begin(); ites != pair_container.end(); ++ites)
    // {
    //     int first_num = ites->first;
    //     int second_num = ites->second;
    //     std::list<std::pair<int, int> >::iterator insertion_point = ites;

    //     // while (insertion_point != pair_container.begin() && first_num < (--insertion_point)->first)
    //     while (insertion_point != pair_container.begin() && first_num < (--insertion_point)->first)
    //     {
    //         // Move the iterator back and swap the elements
    //         std::pair<int, int>& curr = *insertion_point;
    //         std::pair<int, int>& prev = *(++insertion_point);
    //         prev.first = curr.first;
    //         prev.second = curr.second;
    //         curr.first = first_num;
    //         curr.second = second_num;
            
    //     }
    // }

    std::list<std::pair<int, int> >::iterator ites = pair_container.begin();
    ++ites; // Start from the second element since the first element is considered sorted initially

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
    // print the pairs and check if they are sorted
    // std::cout << "\nprint the pairs and check if they are sorted" << std::endl;
    // for (std::list<std::pair<int, int> >::iterator ites = pair_container.begin(); ites != pair_container.end(); ++ites)
    //     std::cout << ites->first << " " << ites->second << std::endl << std::endl;

    // split the pairs into main chain and pend chain
    std::list<int> first_chain;
    std::list<int> second_chain;
    std::list<std::pair<int, int> >::iterator it_chains = pair_container.begin();
    for (; it_chains != pair_container.end(); ++it_chains)
    {
        first_chain.push_back(it_chains->first);
        second_chain.push_back(it_chains->second);
    }
    // Insert the second element from the first pair to the beginning of the first_chain
    // first_chain.push_front(pair_container.begin()->second);

    // print the first chain and second chain
    std::cout << "first chain: ";
    for (std::list<int>::iterator it = first_chain.begin(); it != first_chain.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "\nsecond chain: ";
    for (std::list<int>::iterator it = second_chain.begin(); it != second_chain.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    // need to implement the algo
    
    // filling the jacobsthal list according to second chain size starting from 3

    size_t second_chain_size = second_chain.size();
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
        }
        starting_index++;
    }

    // print the jacobsthal list
    // std::cout << "\njacobsthal list: ";
    // for (std::list<int>::iterator it = jacobsthal_list.begin(); it != jacobsthal_list.end(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;
    

    // using binary search to insert the second chain elements into the first chain in the right place
    // iterate through the jacobsthal_list.size()

    insert_second_chain(first_chain, second_chain);

    // printin the first chain
    // std::cout << "first chain after: ";
    // for (std::list<int>::iterator it = first_chain.begin(); it != first_chain.end(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;
    // std::cout << "second chain after: ";
    // for (std::list<int>::iterator it = second_chain.begin(); it != second_chain.end(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;

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

// void    PmergeMe::insert_second_chain(std::list<int> &first_chain, std::list<int> &second_chain)
// {
//     // second chain = 2, 49, 3
//     // first chain = 2, 44, 52, 97
//     // jacoblist = 3, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14
//     // i want to insert the second chain into the first chain in a sorted way using jacobshtal list as a reference

//     // first i need to find the index of the second chain element in the jacobsthal list
//     // for the first time we will take the first number in jacoblist `3` and to index it will be `3 - 1 =2` so we will go the index 2 in the second chain and find the accurate position to put it into the first chain
//     // code:
//     // 1- iterate through the jacobsthal list
//     // 2- for each element in the jacobsthal list we will find the index of the element in the second chain
//     // 3- we will insert the element in the first chain in the right place so that the first chain should be sorted
//     // 4- we will remove the element from the second chain
//     // 5- we will repeat the process until the second chain is empty

//     std::list<int> jacobsthal_list_copy = jacobsthal_list;
//     std::vector<bool> dp(first_chain.size(), false); // Initialize a DP vector to track inserted elements
//     // std::cout << "jacob list copy: ";
//     // for (std::list<int>::iterator it = jacobsthal_list.begin(); it != jacobsthal_list.end(); ++it)
//     //     std::cout << *it << " ";
//     // std::cout << std::endl;
//     std::list<int>::iterator it_jcb = jacobsthal_list_copy.begin();
//     std::list<int>::iterator it_second_chain;
//     std::list<int>::iterator it_first_chain;
//     int jcb_index = 0;
//     int jcb_element;
//     for (; jcb_index < (int)jacobsthal_list_copy.size(); ++it_jcb)
//     {
//         jcb_element = *it_jcb - 1; // 3 - 1 = 2; so we should take the second element of second_chain
//         // std::cout << "______________" << std::endl;
//         // std::cout << "jcb index: " << jcb_index << std::endl;
//         // std::cout << "jcb element: " << jcb_element << std::endl;
//         it_second_chain = second_chain.begin();
//         for (int i = 1; i < jcb_element; i++)
//         {
//             it_second_chain++;
//         }
//         it_first_chain = first_chain.begin();
//         // while (it_first_chain != first_chain.end())
//         // {
//         //     if (*it_first_chain > *it_second_chain)
//         //     {
//         //         first_chain.insert(it_first_chain, *it_second_chain);
//         //         break;
//         //     }
//         //     it_first_chain++;
//         // }
//         // jcb_index++;
//         // if (first_chain.size() == listContainer.size())
//         //     break;

//         for (int i = 0; i < (int)first_chain.size(); i++)
//         {
//             if (dp[i] == false && *it_first_chain > *it_second_chain)
//             {
//                 first_chain.insert(it_first_chain, *it_second_chain);
//                 dp[i] = true;
//                 break;
//             }
//             it_first_chain++;
//         }
//         jcb_index++;
//         if (first_chain.size() == listContainer.size())
//             break;

//         // std::cout << "printing the first chaine: " << std::endl;
//         // for (std::list<int>::iterator it = first_chain.begin(); it != first_chain.end(); ++it)
//         //     std::cout << *it << " ";
//         // std::cout << std::endl;
//         // std::cout << "______________" << std::endl;
//     }
// }
void PmergeMe::insert_second_chain(std::list<int> &first_chain, std::list<int> &second_chain)
{
    std::list<int> jacobsthal_list_copy = jacobsthal_list;
    std::list<int>::iterator it_jcb = jacobsthal_list_copy.begin();
    std::vector<bool> second_chain_inserted(second_chain.size(), false);
    std::list<int>::iterator it_second_chain;
    std::list<int>::iterator it_first_chain;

    std::cout << std::endl;
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
        // std::cout << "______________" << std::endl;
        //     std::cout << "dp value: " << second_chain_inserted[jcb_element % second_chain.size()] << std::endl;
        while (it_first_chain != first_chain.end())
        {
            if (second_chain_inserted[jcb_element % second_chain.size()] == true)
                break;
            if (*it_first_chain > *it_second_chain)
            {
                // std::cout << "dkhlaaat" << std::endl;
                first_chain.insert(it_first_chain, *it_second_chain);
                second_chain_inserted[jcb_element % second_chain.size()] = true;
                break;
            }
            ++it_first_chain;
        }
        ++it_jcb;
        //         std::cout << "printing the first chaine: " << std::endl;
        // for (std::list<int>::iterator it = first_chain.begin(); it != first_chain.end(); ++it)
        //     std::cout << *it << " ";
        // std::cout << std::endl;
        // std::cout << "number inserted: " << *it_second_chain << std::endl;
    }
}





// /*
// 1- create the pair
// 2- sort the pair
// 3- sort
// 4- 
// */

void    PmergeMe::sorting_deque()
{
    // doing same thing as the list container expect that we will use deque container
    size_t size = dequeContainer.size();
    std::deque<std::pair<int, int> > pair_container;

    if (size < 2)
        return ;
    
    int div = size / 2;
    int i = 0;
    // i am not supposed to use iterators if i can use other methods of deque to make things faster
    std::deque<int>::iterator it = dequeContainer.begin();
    while (div > 0)
    {
        pair_container.push_back(std::make_pair(*it, *(++it)));
        div--;
        i += 2;
        it++;
    }

    // priting the pairs
    // for (std::deque<std::pair<int, int> >::iterator it = pair_container.begin(); it != pair_container.end(); ++it)
    //     std::cout << it->first << " " << it->second << std::endl;

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

    // print the pairs and check if they are sorted
    // for (std::deque<std::pair<int, int> >::iterator ites = pair_container.begin(); ites != pair_container.end(); ++ites)
    //     std::cout << ites->first << " " << ites->second << std::endl;
    
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

    // print the pairs and check if they are sorted
    // std::cout << "\nprint the pairs and check if they are sorted" << std::endl;
    // for (std::deque<std::pair<int, int> >::iterator ites = pair_container.begin(); ites != pair_container.end(); ++ites)
    //     std::cout << ites->first << " " << ites->second << std::endl << std::endl;

    // split the pairs into main chain and pend chain
    std::deque<int> first_chain;
    std::deque<int> second_chain;
    for (size_t i = 0; i < (size_t)pair_container.size(); i++)
    {
        first_chain.push_back(pair_container[i].first);
        second_chain.push_back(pair_container[i].second);
    }

    // print the first chain and second chain
    // std::cout << "first chain: ";
    // for (std::deque<int>::iterator it = first_chain.begin(); it != first_chain.end(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;
    
    // std::cout << "\nsecond chain: ";
    // for (std::deque<int>::iterator it = second_chain.begin(); it != second_chain.end(); ++it)
    //     std::cout << *it << " ";
    // std::cout << std::endl;

    // need to implement the algo
    std::deque<int> jacobsthal_deque;
    int second_chain_size = second_chain.size();
    std::cout << "second chain size: " << second_chain_size << std::endl;
    int a = 1;
    int b = 1;
    int c;
    int flag = 2;
    // while ((c = a + 2 * b) <= second_chain_size)
    for (int i = 0; i < second_chain_size; i++)
    {
        c = b + (2 * a);
        std::cout << "c: " << c << std::endl;
        jacobsthal_deque.push_back(c);
        // 3 2 5 4 11 10 9 8 7 6
        // after pushing a jacob sequence starting from number 3 we need to push the rest of the numbers
        // 3 2 5 4 11 10 9 8 7 6
        for (int j = c - 1; j >= flag; j--)
        {
            if (std::find(jacobsthal_deque.begin(), jacobsthal_deque.end(), j) == jacobsthal_deque.end())
                jacobsthal_deque.push_back(j);
        }
        a = b;
        b = c;
        flag = c;
    }

    // print the jacobsthal deque
    std::cout << "\njacobsthal deque: ";
    for (int i = 0; i < (int)jacobsthal_deque.size(); i++)
        std::cout << jacobsthal_deque[i] << " ";
    std::cout << std::endl;
}