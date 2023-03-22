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

// int BitcoinExchange::find_closest_date(const std::string &date) const
// {
//     int year, month, day;
//     parse_date(date, year, month, day);
//     int closest_index = 0;
//     int closest_distance = 1000000;
//     for (size_t i = 0; i < exchange_rates.size(); i++)
//     {
//         int year2, month2, day2;
//         parse_date(exchange_rates[i].date, year2, month2, day2);
//         int distance = abs(year - year2) * 365 + abs(month - month2) * 30 + abs(day - day2);
//         if (distance < closest_distance)
//         {
//             closest_distance = distance;
//             closest_index = i;
//         }
//     }
//     return (closest_index);
// }

int BitcoinExchange::find_closest_date(const std::string &date) const
{
    // parse the input date using parse_date function
    int year, month, day;
    parse_date(date, year, month, day);

    // find the closest date using std::lower_bound;
    std::vector<exchange_rate_row>::const_iterator it;
    it = std::lower_bound(exchange_rates.begin(), exchange_rates.end(), search_row, Compare_exchange_rate_rows())
    {
        return (a.date < b.date);
    });

    // if the date is not found or it's the first element, return 0
    if (it == exchange_rates.end() || it == exchange_rates.begin())
        return (0);
    
    // Check which element is closer to the search date
    std::vector<exchange_rate_row>::const_iterator prev_it = it - 1;
    int prev_year, prev_month, prev_day;

    parse_date(prev_it->date, prev_year, prev_month, prev_day);
    double diff1 = fabs(difftime(mktime(&tm{0,0,0,prev_day,prev_month-1,prev_year-1900}), mktime(&tm{0,0,0,day,month-1,year-1900})));
    
    int next_year, next_month , next_day;
    parse_date(it->date, next_year, next_month, next_day);
    double diff2 = fabs(difftime(mktime(&tm{0,0,0,next_day,next_month-1,next_year-1900}), mktime(&tm{0,0,0,day,month-1,year-1900})));

    if (diff1 < diff2)
        return (prev_it - exchange_rates.begin());
    return (it - exchange_rates.begin());
}

void    BitcoinExchange::parse_date(const std::string &date, int &year, int &month, int &day) const
{
    struct std::tm timeinfo = {};
    std::istringstream ss(date);
    ss >> std::get_time(&timeinfo, "%Y-%m-%d");

    year = timeinfo.tm_year + 1900;
    month = timeinfo.tm_mon + 1;
    day = timeinfo.tm_mday;
}