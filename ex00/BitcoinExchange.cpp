#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &input_filename)
{
    parse_input_file(input_filename);
    parse_csv_file("data.csv");
}

BitcoinExchange::~BitcoinExchange()
{
}

void    BitcoinExchange::parse_input_file(const std::string &input_file)
{
    std::ifstream file(input_file.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        exit (1);
    }
    std::string line;
    getline(file, line); // skip the header row

    while (getline(file, line))
    {
        exchange_rate_row row = parse_input_row(line, '|');
        input_file_data.push_back(row);
    }
}

BitcoinExchange::exchange_rate_row BitcoinExchange::parse_input_row(const std::string &input_row, char delimiter)
{
    exchange_rate_row row;
    std::stringstream ss(input_row);
    getline(ss, row.date, delimiter);
    ss >> row.rate;
    if (ss.fail() || row.rate <= 0 || row.date.empty() || row.rate > 1000)
    {
        std::cerr << "Error: invalid input file." << std::endl;
        exit (1);
    }
    return (row);
}

void BitcoinExchange::parse_csv_file(const std::string &csv_file)
{
    std::ifstream csv(csv_file.c_str());
    if (!csv.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        exit(1);
    }
    std::string line;
    getline(csv, line); // skip the header row

    while (getline(csv, line))
    {
        exchange_rate_row row = parse_input_row(line, ',');
        exchange_rates.push_back(row);
    }
}

int BitcoinExchange::find_closest_date(const std::string &date) const
{
    int index = -1;
    int min_diff = std::numeric_limits<int>::max();

    for ()
}