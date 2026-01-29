/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:10:59 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/08 00:53:38 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HumanB.hpp"

HumanB::HumanB(){
    
}

HumanB::HumanB(const std::string& name) : weapon(NULL), name(name){

}

HumanB::~HumanB(){

}

void HumanB::setWeapon(Weapon& weapon){
    this->weapon = &weapon;
}

void HumanB::attack() {
    if (weapon)
        std::cout << name << " attacks with their " << weapon->getType() << std::endl;
    else
        std::cout << name << " has no weapon to attack" << std::endl;
}