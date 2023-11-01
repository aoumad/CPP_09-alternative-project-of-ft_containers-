/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:28:53 by aoumad            #+#    #+#             */
/*   Updated: 2023/11/01 18:20:56 by aoumad           ###   ########.fr       */
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
        this->_res = rhs._res;
    }
    return *this;
}

void    RPN::calc(std::string input)
{
    std::istringstream iss(input);
    std::string token;
    int op1, op2;
    std::string op;

    while (iss >> op)
    {
        if (op.size() > 1)
        {
            std::cerr << "Error" << std::endl;
            exit(1);
        }
        if (isdigit(op[0]) && atoi(op.c_str()) < 10)
            this->_stack.push(atoi(op.c_str()));
        else if (op == "+" || op == "-" || op == "*" || op == "/")
        {
            if (this->_stack.size() < 2)
            {
                std::cerr << "Error: Not enough numbers to make an operation" << std::endl;
                exit(1);
            }
            op2 = this->_stack.top();
            this->_stack.pop();
            op1 = this->_stack.top();
            this->_stack.pop();

            switch(op[0])
            {
                case '+':
                    this->_stack.push(op1 + op2);
                    break;
                case '-':
                    _stack.push(op1 - op2);
                    break;
                case '*':
                    _stack.push(op1 * op2);
                    break;
                case '/':
                    if (op2 == 0)
                    {
                        std::cerr << "Error: Division by zero" << std::endl;
                        exit(1);
                    }
                    this->_stack.push(op1 / op2);
                    break;
            }
        }
        else
        {
            std::cerr << "Error" << std::endl;
            exit(1);
        }
    }
    
    if (this->_stack.size() != 1)
    {
        std::cerr << "Error: Too many numbers in the stack" << std::endl;
        std::cerr << "caution: it might be the last argument is a number and not an operator" << std::endl;
        exit(1);
    }

    this->_res = this->_stack.top();
    this->_stack.pop();
    std::cout << this->_res << std::endl;
}