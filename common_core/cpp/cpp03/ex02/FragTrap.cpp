/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:19:00 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/12 13:41:52 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("DefaultFrag") {
    std::cout << "Default constructor FragTrap called"
                << std::endl;
    this->_hit_points = 100;
    this->_energy_points = 100;
    this->_attack_damage = 30;
}   


FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
    std::cout << "FragTrap constructor with name called" 
                << std::endl;
    this->_hit_points = 100;
    this->_energy_points = 100;
    this->_attack_damage = 30;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other){
        std::cout << "FragTrap copy constructor called"
                    << std::endl;
}
    
FragTrap& FragTrap::operator=(const FragTrap& other) {
        
    if (this != &other) {
            ClapTrap::operator=(other);
    }
        std::cout << "FragTrap assignment operator called" << std::endl;
        return *this;
    }

FragTrap::~FragTrap(){
        std::cout << "Destructor FragTrap called"
                    << std::endl;
}

void FragTrap::attack(const std::string& target){
    if (this->_energy_points == 0)
    {
        std::cout << "No ressources to attack the target"
                    << std::endl;
        return ;
    }
    std::cout << "FragTrap "
                << this->_name
                << " attacks "
                << target
                << " causing "
                <<  this->_attack_damage
                << " points of damage"
                << std :: endl;

    this->_energy_points--;
}


void FragTrap::highFivesGuys(void){
    std::cout << "FragTrap " 
                << this->_name 
                << " requests a high five! ✋😃" 
                << std::endl;
}
