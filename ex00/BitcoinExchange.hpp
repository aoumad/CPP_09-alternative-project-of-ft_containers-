#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <vector>
#include <fstream.hpp>
#include <iostream>

class BitcoinExchange
{
    private:
        struct exchange_rate_row
        {
            std::string date;
            double      rate;
        };
        // Vector to hold the exchange rate database
        std::vector<exchange_rate_row>  exchange_rates;

        // function to read the exchange rate databse from a csv_file
        void   parse_csv(const std::string &csv_file);

        // function to parse a single row of the csv file from a string
        exchange_rate_row parse_csv_row(const std::string &csv_row);

        // function to find the index of the closest date in the database
        int    find_closest_date(const std::string &date) const;

        // function to parse a date string into a year, month and a day
        void   parse_date(const std::string &date, int &year, int &month, int &day) const;
    public:
        BitcoinExchange(const std::string &input_filename);
        ~BitcoinExchange();

        // function that takes a filename for a file containing dates and values
        // and prints the value multiplied by the exchange rate for the closest date in the database
        void    print_input_file(const std::string &input_filename);
}

#endif