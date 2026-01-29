/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:17:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/13 12:43:19 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main(){
    
    ClapTrap clap("Soldier");
    FragTrap frag("Referee");
    ScavTrap scav("Ennemy");
    DiamondTrap dia("Coach");
    
    std::cout << std::endl;

    for (int i = 0; i < 3; i++)
    {
        dia.attack(frag.getName()); //valeur d attack damge base sur fragtrap
        frag.takeDamage(30);        //hit points base sur fragtrap
        frag.attack(dia.getName());
        dia.takeDamage(30);
    }   // dia energy points - 3
    std::cout << std::endl;
    for (int i = 0; i < 2; i++)
    {
        clap.attack(dia.getName());
        dia.takeDamage(10);
        scav.attack(frag.getName()); // scav energy points -2
        frag.takeDamage(10);
    }
    
    std::cout << std::endl;
    dia.attack(clap.getName()); //atack base sur scavtrap, // dia energy points - 1
    std::cout << std::endl;

    //dia energy points = 46 et scav energy points = 48
    for (int i = 0; i < 50; i++)
    {
        dia.attack("The void");
        scav.attack("The void too");
    }
    
    return (0);
}
