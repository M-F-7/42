/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/11 18:33:36 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"



int main(int ac, char **av){

    if (ac != 2)
    {
        std::cout << "[ Probably complaining about insignificant problems ]"
                    << std::endl;
        return 1;
    }
    Harl Foo;
    Foo.complain(av[1]);
    std::cout << std::endl;
    
    return 0;
}