/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:31:49 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/21 10:38:07 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"

int main( void ) {
    int tab[] = {0, 1, 2, 3};
    iter(tab, 4, f);
    for (int i = 0; i < 4; i++)
        std::cout << tab[i] << std::endl;
    std::cout << "-------------------------"
                << std::endl;
    
    float tab1[] = {0.5, 1.5, 2.5, 3.5};
    iter(tab1, 4.0f, f);
    for (int i = 0; i < 4; i++)
        std::cout << tab1[i] << "f" << std::endl;
    std::cout << "-------------------------"
                << std::endl;
    
    double tab2[] = {0.2, 1.2, 2.2, 3.2};
    iter(tab2, 4.0, f);
    for (int i = 0; i < 4; i++)
        std::cout << tab2[i] << std::endl;
    std::cout << "-------------------------"
                << std::endl;
    
    char tab3[] = "abcd";
    iter(tab3, 4, f);
    for (int i = 0; i < 4; i++)
        std::cout << tab3[i] << std::endl;
    std::cout << "-------------------------"
                << std::endl;
}