/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:28:50 by aoumad            #+#    #+#             */
/*   Updated: 2023/10/29 14:11:23 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <sstream>
# include <exception>

class RPN
{
    private:
        std::stack<double>  _stack;
        long                _res;
    
    public:
        RPN(void);
        RPN(RPN const &src);
        ~RPN(void);

        RPN &operator=(RPN const &rhs);
        void    calc(std::string input);
};

#endif