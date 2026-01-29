/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:52:24 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/13 12:39:18 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
    : ClapTrap("DiamondTrap_clap_name"), FragTrap(), ScavTrap(), _name("DiamondTrap") {
    std::cout << "Default constructor DiamondTrap called" << std::endl;
    this->_hit_points = FragTrap::_hit_points; // 100
    this->_energy_points = ScavTrap::_energy_points; // 50
    this->_attack_damage = FragTrap::_attack_damage; //30
}


DiamondTrap::DiamondTrap(const std::string& name)
    : ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name), _name(name) {
    std::cout << "DiamondTrap constructor with name called" << std::endl;
    this->_hit_points = FragTrap::_hit_points;
    this->_energy_points = ScavTrap::_energy_points;
    this->_attack_damage = FragTrap::_attack_damage;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other)
    : ClapTrap(other), FragTrap(other), ScavTrap(other), _name(other._name) {
    std::cout << "DiamondTrap copy constructor called"
                << std::endl;   
    this->_hit_points = other._hit_points;
    this->_energy_points = other._energy_points;
    this->_attack_damage = other._attack_damage;
}
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other);
        ScavTrap::operator=(other);
        FragTrap::operator=(other);
        this->_name = other._name;
        this->_hit_points = other._hit_points;
        this->_energy_points = other._energy_points;
        this->_attack_damage = other._attack_damage;
    }
    std::cout << "DiamondTrap assignment operator called" << std::endl;
    return *this;
}

DiamondTrap::~DiamondTrap(){
        std::cout << "Destructor DiamondTrap called"
                    << std::endl;
}


void DiamondTrap::whoAmI(){
    std::cout << "Diamond Trap name: "
                << this->_name
                << std::endl
                <<"Clap Trap name: "
                << ClapTrap::_name
                << std::endl;
}

void DiamondTrap::attack(const std::string& target) {
    ScavTrap::attack(target);
}

std::string DiamondTrap::getName() const {
    return this->_name;
}