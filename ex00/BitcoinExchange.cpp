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

int BitcoinExchange::find_closest_date(const std::string& date) const
{
    // Convert the input date to a row with a dummy rate
    exchange_rate_row search_row = { date, 0.0 };

    // Find the closest date using std::lower_bound
    std::vector<exchange_rate_row>::const_iterator it =
        std::lower_bound(exchange_rates.begin(), exchange_rates.end(), search_row,
                         [](const exchange_rate_row& a, const exchange_rate_row& b) {
                             return a.date < b.date;
                         });

    // If the date is not found or it's the first element, return 0
    if (it == exchange_rates.end() || it == exchange_rates.begin())
    {
        return 0;
    }

    // Check which element is closer to the search date
    std::vector<exchange_rate_row>::const_iterator prev_it = it - 1;
    double diff1 = fabs(difftime(strptime(search_row.date.c_str(), "%Y-%m-%d", nullptr), strptime(prev_it->date.c_str(), "%Y-%m-%d", nullptr)));
    double diff2 = fabs(difftime(strptime(search_row.date.c_str(), "%Y-%m-%d", nullptr), strptime(it->date.c_str(), "%Y-%m-%d", nullptr)));

    if (diff1 < diff2)
    {
        return prev_it - exchange_rates.begin();
    }
    else
    {
        return it - exchange_rates.begin();
    }
}


/*
In the find_closest_date function, the line exchange_rate_row search_row = { date, 0.0 } is creating a new exchange_rate_row object named search_row, which is used to find the closest date to the input date.

exchange_rate_row is a user-defined struct that contains two data members: date, which represents the date of the exchange rate, and rate, which represents the exchange rate on that date.

So in the line of code in question, we are creating a new exchange_rate_row object and initializing its date member to the date input parameter and its rate member to 0.0.

The purpose of initializing the rate member to 0.0 is to create a "dummy" row that can be used as a starting point for the search algorithm to find the closest date. This search_row object will be compared to the other rows in the exchange_rate_table to determine which row has the closest date to the input date.

Essentially, the search_row object is a reference point for finding the closest date in the exchange_rate_table.
*/