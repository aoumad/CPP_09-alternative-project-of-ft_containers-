/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:28:55 by aoumad            #+#    #+#             */
/*   Updated: 2023/03/23 14:14:32 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: Invalid number of arguments." << std::endl;
        std::cerr << "Usage: ./RPN \"7 7 * 7 -\"" << std::endl;
        return 1;
    }

    std::string input = argv[1];
    for (int i = 2; i < argc; i++)
    {
        input += " ";
        input += argv[i];
    }

    std::istringstream iss(input);
    std::stack<double> st;
    std::string token;
    double op1, op2;
    char op;

    while (iss >> op)
    {
        if (isdigit(op))
            st.push(op - '0');
        else if (op == '+' || op == '-' || op == '*' || op == '/')
        {
            if (st.size() < 2)
            {
                std::cerr << "Error: Not enough operands." << std::endl;
                return 1;
            }
            op2 = st.top();
            st.pop();
            op1 = st.top();
            st.pop();

            switch (op)
            {
                case '+':
                    st.push(op1 + op2);
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
                        std::cerr << "Error: Division by zero." << std::endl;
                        return 1;
                    }
                    st.push(op1 / op2);
                    break;
            }
        }
        else
        {
            std::cerr << "Error: Invalid operator." << std::endl;
            return 1;
        }
    }
    
    if (st.size() != 1)
    {
        std::cerr << "Error: Too many operands." << std::endl;
        return 1;
    }
    
    std::cout << st.top() << std::endl;
    return 0;
}