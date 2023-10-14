#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int count, char **argv)
{
    std::string s;
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
    }
}


bool    input_parsing(std::string s)
{
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    int num;

    if (s.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cerr << "Error: non numeric arguments" << std::endl;
        return (false);
    }
    // get the length of the string
    int len = std::strlen(s);
    if (len > 10 && s.find_first_not_of(" ") != std::string::npos)
    {
        std::cerr << "Error: the number is too long" << std::endl;
        return (false);
    }

    std::istringstream(s) >> num;

    if (std::istringstream(s).fail() || num > INT_MAX || s.compare(INT_MAX) == 0)
    {
        std::cerr << "Error: Invalid or out-of-range number: " << num << std::endl;
        return (false);
    }
    
    if (num < 0)
    {
        std::cerr << "Error" << std::endl;
        return (false);
    }

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        if (input_parsing(token) == false)
            return (false);
        s.erase(0, pos + delimiter.length());
    }
}