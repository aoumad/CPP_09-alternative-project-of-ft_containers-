/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:28:55 by aoumad            #+#    #+#             */
/*   Updated: 2023/03/22 17:59:07 by aoumad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: ./RPN \"7 7 * 7 -\"" << std::endl;
        return 1;
    }
    RPN rpn;
    // enter the argv to stack
    for (int i = 0; i < argc; i++)
    
}