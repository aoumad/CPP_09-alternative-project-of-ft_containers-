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
# define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <time.h>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _exchange_rates;
        long    date_to_long(const std::string &date) const;
        // double  _value;
        // std::string _date;
        vector<std::string> _date;
        vector<double> _value;
        double      _rtn_rate;

    public:
        BitcoinExchange();
        BitcoinExchange(std::string input_filename);
        BitcoinExchange(const BitcoinExchange& input_filename);
        ~BitcoinExchange();

        BitcoinExchange & operator=(const BitcoinExchange & rhs);

        void    Input_checker(char *file);
        int     is_valid_line(std::string line);
        int     is_valid_date(std::string date);
        int     is_valid_value(std::string value);
        void    find_closest_date(int i);
};

#endif