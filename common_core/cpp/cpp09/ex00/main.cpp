/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:43:36 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/23 13:22:39 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main (int ac, char **av){

    if (ac != 2)
        return std::cerr << "Error: could not open file." 
                            << std::endl, 1;
   
   std::multimap<std::string, double> db = fill_db();
   if (!db.size())
      return std::cerr << "Invalid data.csv file" << std::endl, 1; 

   std::multimap<std::string, double> input = fill_input(av[1], db);
   if (!input.size())
      return std::cerr << "Invalid infile" << std::endl, 1;
    return 0;
}