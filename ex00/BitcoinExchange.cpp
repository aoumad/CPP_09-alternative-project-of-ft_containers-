/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:47:10 by aoumad            #+#    #+#             */
/*   Updated: 2023/03/22 15:47:12 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string input_filename)
{
    std::ifstream file(input_filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open database file." << std::endl;
        file.close();
        exit(1);
    }

    std::string line;
    std::getline(file, line); // Skip the header row

    while(!file.eof())
    {
        std::getline(file, line);
        try
        {
            _exchange_rates.insert(std::make_pair(line.substr(0, 10), std::stof(line.substr(11))));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            file.close();
        }
    }
    file.close();

    find_closest_date();
}

BitcoinExchange::Input_checker(const char *file)
{
    std::ifstream fs(file);
    std::string date;
    std::string value;
    int         index;

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
        std::cer << "Error: the Input doesn't contain any data!" << std::endl;
        fs.close();
        exit(1);
    }

    index = 0;
    while (std::getline(fs, line))
    {
        if (is_valid_line(line, index))
            exit(1);
        find_accurate_date(index);
    }
}

BitcoinExchange::is_valid_line(std::string line, int i)
{
    size_t index = line.find('|');
    if (index == std::string::npos || line.at(11) != "|" || index != line.rfind('|') || line.size() < 14)
    {
        std::cerr << "Error: " << line << "is incorrect" << std::endl;
        return (true);
    }

    _date[i] = line.substr(0, index);
    _value[i]= line.substr(index + 1);
    if (date[i].empty() || value[i].empty())
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return (true);
    }

    if (is_valid_date(i) || is_valid_value(i))
        return (true);
    
    return (false);
}


BitcoinExchange::is_valid_value(int i)
{
    int count = count(_value[i].begin(), _value[i].end(), '.');

    if (count > 1 || _value[i].find_first_not_of("f0123456789.") != std::string::npos)
    {
        std::cer << "Error: the value " << _value[i] << " is incorrect!" << std::endl;
        return (true);
    }

    _value[i].erase(_value[i].begin()) // in this way i am skipping the space after the vertical bar `|`
    // then we will check if there is minus operator or not
    if (_value[i][0] == '-')
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return (true);
    }

    double nbr = std::stod(_value[i]);
    if (nbr > INT_MAX)
    {
        std::cer << "Error: too large a number." << std::endl;
        return (true);
    }

    _value[i] = nbr;
    return (false);
}

BitcoinExchange::is_valid_date(int i)
{
    int day, month, year;
    char first_del, second_del;
    bool leap_year;

    std::isstringstream ss(_date[i]);
    ss >> year >> first_del >> month >> second_del >> day;
    
    // the ss.fail() check tells us if an input was read
    if (ss.fail() || count(_date[i].begin(), _date[i].end(), '-') != 2 || first_del != '-' || second_del != '-'
        || day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
    {
        std::cerr << "Error: bad input => " << _date[i] << std::endl;
        return (true);
    }

    leap_year = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    /*
    This part of the code checks whether the given year is a leap year. 
    Leap years have an extra day (February 29), and they occur every four years, with some exceptions. 
    The conditions (year % 4 == 0) and (year % 100 != 0) check if the year is divisible by 4 but not divisible by 100. 
    Additionally, (year % 400 == 0) checks if the year is divisible by 400.
    If any of these conditions are true, leap_year is set to true, indicating that it's a leap year.
    */
    if ((month == 2 && (leap_year ? day > 29 : day > 28)) ||
    ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
    {
        std::cerr << "Error: bad input => " << _date[i] << std::endl;
        return (true);
    }

    /*
    In a standard (non-leap) year, February has 28 days. This is because the calendar is designed with 365 days, 
    and February typically has 28 days to keep the total year length close to 365 days.

    In a leap year, an extra day is added to the calendar, making it 366 days in total.
    This extra day is added to the end of February, resulting in February having 29 days instead of the usual 28.
    */

   return (false);
}

void    find_accurate_date(int i) // Binary search approach
{
    std::string input_date = _date[i];
    double minDiff = 1e10; // A large number that serves as an initial maximum
    std::string closest_date = "";

    std::map<std::string, double>::iterator it = _exchange_rates.begin();
    std::map<std::string, double>::iterator end = _exchange_rates.end();

    while (it != end)
    {
        const std::string& data_date = it->first;
        // Calculate the absolute difference between the input date and data date
        double diff = calculate_date_diff(input_date, data_date);

        if (diff < minDiff)
        {
            minDiff = diff;
            closest_date = data_date;
        }

        if (input_date = data_date)
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

}