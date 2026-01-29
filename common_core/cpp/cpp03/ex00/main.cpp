/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:17:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/12 12:09:01 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main(){
    
    ClapTrap foo("Soldier");
    ClapTrap bar("Ennemy");
    
    std::cout << std::endl
                << "FIGHT :"
                << std::endl;
                
    for (int i = 0; i < 10; i++)
    {
        foo.attack(bar.getName());
        bar.takeDamage(1);
    }
    
    std::cout << std::endl
                << " Foo With 0 energy and full life:"
                << std::endl;
                
    foo.beRepaired(1);
    foo.attack(bar.getName());
    
    std::cout << std::endl
                << "Time To Heal :"
                << std::endl;

    for (int j = 0; j <10; j++)
        bar.beRepaired(1);
    
    std::cout << std::endl
                << "Bar With 0 energy and full life:"
                << std::endl;
    
    bar.attack(foo.getName());
    bar.beRepaired(1);
    std::cout << std::endl;
    return (0);
}
