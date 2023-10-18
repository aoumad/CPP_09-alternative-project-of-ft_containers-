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

void    RPN::calc(std::string input)
{
    std::istringstream iss(input);
    std::string token;
    int op1, op2;
    char op;

    while (iss >> op)
    {
        if (isdigit(op) && (op - '0') < 10)
            this->_stack.push(op - '0');
        else if (op == '+' || op == '-' || op == '*' || op == '/')
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

            switch(op)
            {
                case '+':
                    this->_stack.push(op1 + op2);
                    break;
                case '-':
                    st.push(op1 - op2);
                    break;
                case '*':
                    st.push(op1 * op2);
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
            std::cerr << "Error: Invalid input" << std::endl;
            exit(1);
        }
    }
    
    if (this->_stack.size() != 1)
    {
        std::cerr << "Error: Too many numbers in the stack" << std::endl;
        std::cerr << "caution: it might be the last argument is a number and not an operator" << std::endl;
        exit(1);
    }
}