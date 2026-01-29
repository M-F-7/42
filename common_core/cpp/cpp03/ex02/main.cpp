/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:17:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/12 13:49:39 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(){
    
    ClapTrap foo("Soldier");
    ScavTrap bar("Ennemy");
    FragTrap ref("Referee");
    std::cout << std::endl;

    bar.guardGate();
    std::cout << std::endl;
    ref.highFivesGuys();
    std::cout << std::endl;
    
    for (int i = 0; i < 100; i++)
    {
        ref.attack(bar.getName());
        bar.takeDamage(30);
    }
    
    std::cout << std::endl;
    
    ref.attack(foo.getName());
    
    std::cout << std::endl;

    for (int i = 0; i < 10; i++)
    {
        foo.attack(ref.getName());
        bar.attack(ref.getName());
        ref.takeDamage(10);
    }

    std::cout << std::endl;
    
    ref.takeDamage(150);
    
    std::cout << std::endl;
    return (0);
}
