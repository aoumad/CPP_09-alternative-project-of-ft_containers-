/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <abderazzakoumad@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:28:55 by aoumad            #+#    #+#             */
/*   Updated: 2023/10/29 14:11:20 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        RPN rpn;
        try
        {
            rpn.calc(std::string(argv[1]));
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
    else
    {
        std::cerr << "Error: invalid numbers of arguments" << std::endl;
        return (1);
    }
}