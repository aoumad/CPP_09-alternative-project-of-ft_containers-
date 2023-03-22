/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoumad <aoumad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:28:50 by aoumad            #+#    #+#             */
/*   Updated: 2023/03/22 17:11:43 by aoumad           ###   ########.fr       */
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
    
    public:
        RPN(void);
        RPN(RPN const &src);
        ~RPN(void);

        RPN &operator=(RPN const &rhs);

        void    push(double value);
        void    pop(void);
        void    dump(void);
        void    assert_(double value);
        void    add(void);
        void    sub(void);
        void    mul(void);
        void    div(void);
        void    print(void);
        void    exit(void);
};

#endif