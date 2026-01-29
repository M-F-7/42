/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/11 18:50:23 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"


int main(){

    Harl Foo;
    
    std::cout << "DEBUG: ";
    Foo.complain("DEBUG");

    std::cout << std::endl;

    std::cout << "INFO: ";
    Foo.complain("INFO");

    std::cout << std::endl;

    std::cout << "WARNING: ";
    Foo.complain("WARNING");
    
    std::cout << std::endl;

    std::cout << "ERROR: ";
    Foo.complain("ERROR");

    std::cout << std::endl;

    return (0);
}