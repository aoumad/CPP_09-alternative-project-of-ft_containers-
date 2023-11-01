/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:47:10 by aoumad            #+#    #+#             */
/*   Updated: 2023/11/01 18:20:42 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& input_filename)
{
    *this = input_filename;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange & rhs)
{
    if (this != &rhs)
    {
        this->_exchange_rates = rhs._exchange_rates;
        this->_closest_date = rhs._closest_date;
        this->_map = rhs._map;
        this->_rtn_rates = rhs._rtn_rates;
        this->_rtn_rate = rhs._rtn_rate;
        this->_curr_date = rhs._curr_date;
        this->_curr_value = rhs._curr_value;
    }
    return *this;
}

BitcoinExchange::BitcoinExchange(char *input_filename)
{
    try
    {
        fill_the_map();
        Input_checker(input_filename);
        for (size_t i = 0; i < _rtn_rates_index; i++)
        {
            std::map<double, std::string>::iterator it = this->_rtn_rates.find(i);
            if (it != _rtn_rates.end())
                std::cout << it->second << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

BitcoinExchange::~BitcoinExchange()
{
}

int BitcoinExchange::is_valid_date(std::string date)
{
    int day, month, year;
    char first_del, second_del;
    bool leap_year;

    std::istringstream ss(date);
    ss >> year >> first_del >> month >> second_del >> day;
    // the ss.fail() check tells us if an input was read
    if (ss.fail() || count(date.begin(), date.end(), '-') != 2 || first_del != '-' || second_del != '-'
        || day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
    {
        this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: bad input => " + date));
        _curr_date = "false";
        return (false);
    }

    leap_year = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    /*
    This part of the code checks whether the given year is a leap year. 
    Leap years have an extra day (February 29), and they occur every four years, with some exceptions. 
    The conditions (year % 4 == 0) and (year % 100 != 0) check if the year is divisible by 4 but not divisible by 100. 
    Additionally, (year % 400 == 0) checks if the year is divisible by 400.
    If any of these conditions are true,  leap_year is set to true, indicating that it's a leap year.
    */
    if ((month == 2 && (leap_year ? day > 29 : day > 28)) ||
    ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
    {
        this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: bad input => " + date));
        _curr_date = "false";
        return (false);
    }

    /*
    In a standard (non-leap) year, February has 28 days. This is because the calendar is designed with 365 days, 
    and February typically has 28 days to keep the total year length close to 365 days.

    In a leap year, an extra day is added to the calendar, making it 366 days in total.
    This extra day is added to the end of February, resulting in February having 29 days instead of the usual 28.
    */
    _curr_date = date;
    return (true);
}

void    BitcoinExchange::find_accurate_date()
{
    std::string input_date = _curr_date;
    double minDiff = 1e10; // A large number that serves as an initial maximum

    std::map<std::string, double>::iterator it = this->_exchange_rates.begin();
    std::map<std::string, double>::iterator end = this->_exchange_rates.end();
    std::string closest_date = "nothing";

    while (it != end)
    {
        const std::string& data_date = it->first;
        // Calculate the absolute difference between the input date and data date
        double diff = calculate_date_diff(input_date, data_date);

        if (diff < minDiff && diff >= 0)
        {
            minDiff = diff;
            closest_date = data_date;
        }

        if (input_date == data_date)
        {
            // an exact match was found, thus we need to exit
            closest_date = data_date;
            break;
        }
        else if (input_date < data_date)
        {
            end = it;
            // in this case it seems that the input date doesn't exist in my DB
            //so i should exit and just get the last value i got so far
        }
        else
            it++;
    }
    if (closest_date == "nothing")
    {
        this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: no data available for this date: " + input_date));
        return ;
    }
    this->_closest_date = closest_date;
    std::map<std::string, double>::iterator ite = _exchange_rates.find(closest_date);
    if (it != _exchange_rates.end())
        this->_rtn_rate = _curr_value * ite->second;

    char buffer[256]; // A buffer to hold the formatted string

    sprintf(buffer, "%s => %.2f = %.2f", _curr_date.c_str(), _curr_value, this->_rtn_rate);
    std::string rtn_string(buffer);
    this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, rtn_string));
}


double  BitcoinExchange::calculate_date_diff(std::string date1, std::string date2)
{
    int year1, month1, day1;
    int year2, month2, day2;

    sscanf(date1.c_str(), "%d-%d-%d", &year1, &month1, &day1); // int sscanf( const char* buffer, const char* format, ... );
    sscanf(date2.c_str(), "%d-%d-%d", &year2, &month2, &day2);

    // Calculating the diff
    int days1 = (year1 * 365 + month1 * 30 + day1);
    int days2 = (year2 * 365 + month2 * 30 + day2);

    return (static_cast<double>((days1 - days2)));
}

// an updated and better function of Input_checker
void    BitcoinExchange::Input_checker(char *file)
{
    std::ifstream fs(file);
    std::string date;
    std::string value;
    // int     index;

   // check the existence of the file
    if (!fs.is_open())
    {
        std::cerr << "Error: Failed to open file!!" << std::endl;
        exit(1);
    }

    // parsing the first line
    std::string line;
    if (!std::getline(fs, line) || line != "date | value")
    {
        std::cerr << "Error: the first line doesn't match the line in the example!!" << std::endl;
        fs.close();
        exit(1);
    }

    if (fs.peek() == std::ifstream::traits_type::eof())
    {
        std::cerr << "Error: the input doesn't contain any data!" << std::endl;
        fs.close();
        exit(1);
    }

    while (std::getline(fs, line))
    {
        if (is_valid_line(line) == true)
            find_accurate_date();
    }
}

int BitcoinExchange::is_valid_line(std::string line)
{
    size_t index = line.find('|');
    std::string value;
    std::string date;
    double rtn_value;
    if (line.empty())
    {
        return (false);
    }
    if (std::all_of(line.begin(), line.end(), isspace))
    {
        return (false);
    }
    if (index == std::string::npos || line.at(11) != '|' || index != line.rfind('|'))
    {
        this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: bad input => " + line));
        return (false);
    }
    
    date = line.substr(0, index);
    value = line.substr(index + 1);
    if (date.empty() || value.empty())
    {
        this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: bad input => " + line));
        return (false);
    }
    if (is_valid_date(date) == false || (rtn_value = is_valid_value(value)) == -1)
        return (false);
    return (true);
}

double BitcoinExchange::is_valid_value(std::string value)
{
    // Remove leading spaces
    while (!value.empty() && std::isspace(value[0]))
        value.erase(0, 1);

    // Remove trailing spaces
    while (!value.empty() && std::isspace(value[value.size() - 1]))
    {
        value.erase(value.size() - 1);
    }
    bool pnt = std::find(value.begin(), value.end(), '.') != value.end();
    if (value.find_first_not_of("0123456789.") != std::string::npos)
    {
        this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: bad input => " + value));
        _curr_value = -1;
        return (-1);
    }

    if (pnt == true)
    {
        // check in case there are more than one `.` in the value string
        std::string::iterator it = std::find(value.begin(), value.end(), '.');
        while (it != value.end())
        {
            it = std::find(it + 1, value.end(), '.');
            if (it != value.end())
            {
                this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: bad input => " + value + " is incorrect!"));
                _curr_value = -1;
                return (-1);
            }
        }
        size_t pnt_index = value.find('.');
        if (pnt_index == 0 || (pnt_index > 0 && !isdigit(value[pnt_index - 1])))
        {
            this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: bad input => " + value + " is incorrect!"));
            _curr_value = -1;
            return (-1);
        }
        if (pnt_index == value.size() - 1 || (pnt_index < value.size() - 1 && !isdigit(value[pnt_index + 1])))
        {
            this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: bad input => " + value + " is incorrect!"));
            _curr_value = -1;
            return (-1);
        }
    }
    // then we will check if there is minus operator or not
    if (value[0] == '-')
    {
        this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: not a positive number."));
        _curr_value = -1;
        return (-1);
    }
    double nbr = std::stod(value);
    if (nbr > 1000)
    {
        this->_rtn_rates.insert(std::pair<double, std::string>(_rtn_rates_index++, "Error: too large a number."));
        _curr_value = -1;
        return (-1);
    }
    _curr_value = nbr;
    // _value.push_back(nbr);
    return (nbr);
}

void    BitcoinExchange::fill_the_map()
{
    // open data.csv file
    std::ifstream fs("data.csv");

    // check the existence of the file
    if (!fs.is_open())
    {
        std::cerr << "Error: Failed to open data.csv file!!" << std::endl;
        exit(1);
    }

    // check the first line syntax and skip it
    std::string line;
    if (!std::getline(fs, line) || line != "date,exchange_rate")
    {
        std::cerr << "Error: the first line doesn't match the line in the example!!" << std::endl;
        fs.close();
        exit(1);
    }
    // now insert the other data into the map 
    while (std::getline(fs, line))
    {
        size_t index = line.find(',');
        this->_exchange_rates.insert(std::pair<std::string, double>(line.substr(0, index), std::stod(line.substr(index + 1))));
    }
    fs.close();
}