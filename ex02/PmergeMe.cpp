#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int count, char **argv)
{
    std::string s;
    numbers = new int[count - 1];
    num_count = 0;

    if (count < 2)
    {
        std::cerr << "Error: Not enough arguments." << std::endl;
        exit(1);
    }
    else
    {
        for (int i = 1; i < count - 1; i++)
        {
            s = argv[i];
            if (input_parsing(s) == false)
                exit(1);
        }
        std::cout << "Before: ";
        for (int i = 1; i < count - 1; i++)
            std::cout << argv[i];
        std::cout << std::endl;
    }

    fill_number_array(count, argv);

    // list Container sorting
    list_start_time = clock();
    for (int i = 0; i < numbers.size(); i++)
        listContainer.push_back(numbers[i]);

    // here i will call the template function that will sort the list
    sorting_container(numbers);

}


bool    PmergeMe::input_parsing(std::string s)
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
    if (len > 10 && s.find_first_not_of(" \"") != std::string::npos)
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

    // Check if the string contains double quotes and remove them
    size_t first_quote = s.find_first_of('"');
    if (first_quote != std::string::npos)
    {
        size_t last_quote = s.find_last_of('"');
        if (last_quote != std::string::npos)
        {
            s = s.substr(first_quote + 1, last_quote - first_quote - 1);
        }
    }

    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        if (input_parsing(token) == false)
            return (false);
        s.erase(0, pos + delimiter.length());
    }

    std::cout << num << " ";

    return (true);
}

void    PmergeMe::fill_number_array(int count, char **argv)
{
    std::string input = "";

    if (count == 2 && argv[i].find_first_not_of(" \"") != std::string::npos)
        fill_special_case(argv);
    else
    {
        for (int i = 1; i < count - 1; i++)
        {
            std::string s = argv[i];
            numbers[i - 1] = atoi(s.c_str());
        }
    }
}

void    PmergeMe::fill_special_case(char **argv)
{
    std::string input = argv[1];

    // remove the double quote `"` from the string
    size_t first_quote = input.find_first_of('"');
    if (first_quote != std::string::npos)
    {
        size_t last_quote = input.find_last_of('"');
        if (last_quote != std::string::npos)
        {
            input = input.substr(first_quote + 1, last_quote - first_quote - 1);
        }
    }

    std::istringstream iss(input);
    int num;
    int num_count = 0;

    while (iss >> num) {
        num_count++;
    }

    if (num_count == 0) {
        std::cerr << "Error: No valid numbers in special case." << std::endl;
        exit(1);
    }

    this->num_count = num_count; // Set the member variable

    numbers = new int[num_count];

    int i = 0;
    while (iss >> num) {
        numbers[i++] = num;
    }
}
PmergeMe::~PmergeMe()
{
    delete[] numbers;
}

template <typename Container>
void    PmergeMe::sorting_container(Container &container, int *numbers)
{
    size_t size = container.size();
    // std::container<std::pair<int, int>> pair_container;
    Container pair_container;
    typename Container::iterator it = container.begin();

    // WSLT HNAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

    if (size < 2)
        return ; // nothing to sort
    
    int rem = size % 2;
    int div = size / 2;
    int i = 0;
    while (div > 0)
    {
        pair_container.push_back(numbers[i], numbers[i + 1]);
        i += 2;
        div--;
    }
}