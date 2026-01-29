/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:51:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/22 15:42:52 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av){
    if (ac != 2)
        return std::cerr << "Error, wrong nb of args" << std::endl, 1;

    try{
        fill_list(av[1]);
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
