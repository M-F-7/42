/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:17:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/12 13:16:14 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main(){
    
    ClapTrap foo("Soldier");
    ScavTrap bar("Ennemy");
    std::cout << std::endl;
    
    bar.guardGate();
    
    std::cout << std::endl
                << "FIGHT:"
                << std::endl;
    for (int i = 0; i < 5; i++)
    {
        bar.attack(foo.getName());
        foo.takeDamage(20);
    }
    
    std::cout << std::endl
                << "REVENGE:"
                << std::endl;
    for (int i = 0; i < 10; i++)
    {
        foo.beRepaired(10);
        foo.attack(bar.getName());
        bar.takeDamage(20);
    }

    std::cout << std::endl
                << "Time to Heal:"
                << std::endl;
    for (int i=0; i < 100; i++)
        bar.beRepaired(1);                  // 45 heal avant de olus avoir de points
                                            // car il a attaque 5 fois au debut
    std::cout << std::endl;
    return (0);
}
