/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:28:53 by aoumad            #+#    #+#             */
/*   Updated: 2023/03/23 14:14:19 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
    return;
}

RPN::RPN(RPN const &src)
{
    *this = src;
    return;
}

RPN::~RPN(void)
{
    return;
}

RPN &RPN::operator=(RPN const &rhs)
{
    if (this != &rhs)
    {
        this->_stack = rhs._stack;
    }
    return *this;
}