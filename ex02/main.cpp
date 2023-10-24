#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 1)
    {
        std::cerr << "Error: The number of arguments isn't enough!" << std::endl;
        exit(1);
    }

    PmergeMe(argc, argv);
}