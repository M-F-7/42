/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:24:26 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/20 23:04:07 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

int  main (int  ac, char **av){
    if (ac !=  2)
    {
        std::cout << "Wrong number of arguments"
                    <<  std::endl;
        return 1;
    }
    ScalarConverter::Convert(av[1]);
    return 0;
}
