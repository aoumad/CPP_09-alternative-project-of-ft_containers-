/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:47:02 by aoumad            #+#    #+#             */
/*   Updated: 2023/10/30 23:39:36 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <vector>
#include <iomanip>
static double _rtn_rates_index = 0;

class BitcoinExchange
{
    private:
        std::map<std::string, double> _exchange_rates;
        long    date_to_long(const std::string &date) const;
        // static double _rtn_rates_index;
        // double  _value;
        std::string _closest_date;
        std::vector<std::string> _date;
        std::vector<double> _value;
        std::map<std::string, double> _map;
        std::map<double, std::string> _rtn_rates;
        double      _rtn_rate;

    public:
        BitcoinExchange();
        BitcoinExchange(char *input_filename);
        BitcoinExchange(const BitcoinExchange& input_filename);
        ~BitcoinExchange();

        BitcoinExchange & operator=(const BitcoinExchange & rhs);

        void    Input_checker(char *file);
        int     is_valid_line(std::string line);
        int     is_valid_date(std::string date);
        double     is_valid_value(std::string value);
        void    find_accurate_date();
        double  calculate_date_diff(std::string date1, std::string date2);
        void    fill_the_map();
};

#endif