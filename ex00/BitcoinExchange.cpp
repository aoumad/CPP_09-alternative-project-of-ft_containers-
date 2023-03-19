#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &input_filename)
{
    parse_csv(input_filename);
}

BitcoinExchange::~BitcoinExchange()
{
}

void    BitcoinExchange::