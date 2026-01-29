/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:53:18 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/24 16:51:29 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av) {
    if (ac < 2) {
        std::cerr << "Error: Wrong number of arguments" << std::endl;
        return 1;
    }

    else if (ac == 2){
        if (av[1][1])
            std::cerr << "Error: dont accept quotes" << std::endl;
        else 
            std::cerr << "Error: need more than one arg to sort" << std::endl;
        return 1;
    }
    
    try {
        PmergeMe v(ac, av);
        v.sort();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
