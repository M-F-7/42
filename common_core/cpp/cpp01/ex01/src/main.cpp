/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/11 18:47:16 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

int main(){

    int n = 5;
    std::string name = "Zombie";
    Zombie *zombie = zombieHorde(n, name);
    if (!zombie)
        std::cout << "Cant announce an empty or negative horde" << std::endl;
    else
        for (int i = 0; i < n; ++i)
            zombie[i].announce();

    Zombie *zomb = zombieHorde(-5, name);
    if (!zomb)
        std::cout << "Cant announce an empty or negative horde" << std::endl;
    else
        for (int i = 0; i < n; ++i)
            zomb[i].announce();

    delete[] zombie;
    return (0);
}