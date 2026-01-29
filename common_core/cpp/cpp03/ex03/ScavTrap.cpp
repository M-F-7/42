/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:10:48 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/13 12:24:42 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("DefaultScav") {
    std::cout << "Default constructor ScavTrap called"
                << std::endl;
    this->_hit_points = 100;
    this->_energy_points = 50;
    this->_attack_damage = 20;
}


ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
    std::cout << "ScavTrap constructor with name called" 
                << std::endl;
    this->_hit_points = 100;
    this->_energy_points = 50;
    this->_attack_damage = 20;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other){
        std::cout << "ScavTrap copy constructor called"
                    << std::endl;
}
    
 ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
        
    if (this != &other) {
            ClapTrap::operator=(other);
    }
        std::cout << "ScavTrap assignment operator called" << std::endl;
        return *this;
    }

ScavTrap::~ScavTrap(){
        std::cout << "Destructor ScavTrap called"
                    << std::endl;
}

void ScavTrap::attack(const std::string& target){
    if (this->_energy_points == 0)
    {
        std::cout << "No ressources to attack the target"
                    << std::endl;
        return ;
    }
    std::cout << "ScavTrap "
                << this->_name
                << " attacks "
                << target
                << " causing "
                <<  this->_attack_damage
                << " points of damage"
                << std :: endl;

    this->_energy_points--;
}
   

void ScavTrap::guardGate() {
    std::cout << "ScavTrap " 
                << this->_name 
                << " is now in Gate keeper mode!" 
                << std::endl;
}
