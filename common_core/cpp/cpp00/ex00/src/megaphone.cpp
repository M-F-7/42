/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:48:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/06 23:25:19 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int ac, char **av){
    
    if (ac < 2)
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    else
    {
        for (int i = 1; av[i]; i++)
            for (int j = 0; av[i][j]; j++)
                std::cout << (char)std::toupper(av[i][j]);
    }
    std::cout << std::endl;
    return (0);
}
