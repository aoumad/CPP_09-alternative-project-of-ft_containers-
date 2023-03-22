/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:47:02 by aoumad            #+#    #+#             */
/*   Updated: 2023/03/22 15:48:12 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <time.h>

class BitcoinExchange
{
    private:
        struct exchange_rate_row
        {
            std::string date;
            double      rate;
        };

        struct Compare_exchange_rate_rows
        {
            bool operator()(const exchange_rate_row &a, const exchange_rate_row &b)
            {
                return (a.date < b.date);
            }
        };
        // Vector to hold the exchange rate database
        std::vector<exchange_rate_row>  exchange_rates;

        // vector to hold the input file data
        std::vector<exchange_rate_row>  input_file_data;

        // function to read the exchange rate databse from a input_file
        void   parse_input(const std::string &input_file);

        // function to parse a single row of the csv file from a string
        exchange_rate_row parse_input_row(const std::string &input_row);

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