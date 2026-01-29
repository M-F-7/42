/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:11:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/08 00:50:16 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HumanA.hpp"

HumanA::HumanA(const std::string& name, Weapon& weapon) : weapon(weapon), name(name) {

}

HumanA::~HumanA(){

}

void HumanA::attack() {
    std::cout << name 
                << " attacks with their " 
                << weapon.getType() 
                << std::endl;
}