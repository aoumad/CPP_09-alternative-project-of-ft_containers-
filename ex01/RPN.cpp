/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:28:53 by aoumad            #+#    #+#             */
/*   Updated: 2023/03/22 17:54:55 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
    return ;
}

RPN::RPN(RPN const &src)
{
    *this = src;
    return ;
}

RPN::~RPN(void)
{
    return ;
}

RPN &RPN::operator=(RPN const &rhs)
{
    if (this != &rhs)
    {
        this->_stack = rhs._stack;
    }
    return *this;
}

void    RPN::push(double value)
{
    this->_stack.push(value);
}

void    RPN::pop(void)
{
    if (this->_stack.empty())
        throw std::exception();
    this->_stack.pop();
}

void    RPN::dump(void)
{
    std::stack<double>  tmp = this->_stack;

    while (!tmp.empty())
    {
        std::cout << tmp.top() << std::endl;
        tmp.pop();
    }
}

void    RPN::assert_(double value)
{
    if (this->_stack.empty())
        throw std::exception();
    if (this->_stack.top() != value)
        throw std::exception();
}

void    RPN::add(void)
{
    if (this->_stack.size() < 2)
        throw std::exception();
    double  a = this->_stack.top();
    this->_stack.pop();
    double  b = this->_stack.top();
    this->_stack.pop();

    this->_stack.push(a + b);
}

void    RPN::sub(void)
{
    if (this->_stack.size() < 2)
        throw std::exception();
    double  a = this->_stack.top();
    this->_stack.pop();
    double  b = this->_stack.top();
    this->_stack.pop();

    this->_stack.push(b - a);
}

void    RPN::mul(void)
{
    if (this->_stack.size() < 2)
        throw std::exception();
    double  a = this->_stack.top();
    this->_stack.pop();
    double  b = this->_stack.top();
    this->_stack.pop();

    this->_stack.push(a * b);
}

void    RPN::div(void)
{
    if (this->_stack.size() < 2)
        throw std::exception();
    double  a = this->_stack.top();
    this->_stack.pop();
    double  b = this->_stack.top();
    this->_stack.pop();

    if (a == 0)
        throw std::exception();
    this->_stack.push(b / a);
}

void    RPN::print(void)
{
    if (this->_stack.empty())
        throw std::exception();
    if (this->_stack.top() < 48 || this->_stack.top() > 57)
        throw std::exception();
    std::cout << static_cast<char>(this->_stack.top()) << std::endl;
}

void    RPN::exit(void)
{
    exit(0);
}