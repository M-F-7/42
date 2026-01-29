/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:16:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/12 17:22:22 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(){
    std::cout << "Default constructor called"
                << std::endl;
}

ClapTrap::ClapTrap(std::string name): _hit_points(10), _energy_points(10), _attack_damage(0){
    std::cout << "Default constructor with name called"
                << std::endl;
    this->_name = name;
}

ClapTrap::ClapTrap(const ClapTrap& other) {
    std::cout << "ClapTrap copy constructor called" << std::endl;
    _name = other._name;
    _hit_points = other._hit_points;
    _energy_points = other._energy_points;
    _attack_damage = other._attack_damage;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
    if (this != &other) {
        _name = other._name;
        _hit_points = other._hit_points;
        _energy_points = other._energy_points;
        _attack_damage = other._attack_damage;
    }
    std::cout << "ClapTrap assignment operator called" << std::endl;
    return *this;
}

ClapTrap::~ClapTrap(){
    std::cout << "Destructor called"
                << std::endl;
}


void ClapTrap::attack(const std::string& target){
    if (this->_energy_points == 0)
    {
        std::cout << "No ressources to attack the target"
                    << std::endl;
        return ;
    }
    std::cout << "Claptrap "
                << this->_name
                << " attacks "
                << target
                << " causing "
                <<  this->_attack_damage
                << " points of damage"
                << std :: endl;

    this->_energy_points--;
}

void ClapTrap::takeDamage(unsigned int amount){
    
    if (this->_hit_points == 0)
    {
        std::cout << "Claptrap "
                    << this->_name
                    << " can't take more damages"
                    << std::endl;
        return ;
    }
    std::cout << "Claptrap "
                << this->_name
                << " has received "
                << amount
                << " points of damage"
                << std::endl;
    if (amount >= this->_hit_points)
        this->_hit_points = 0;
    else
        this->_hit_points -= amount;         
}

void ClapTrap::beRepaired(unsigned int amount){        

    if (this->_hit_points == 10)
    {
        std::cout << "ClapTrap "
                    << this->_name
                    << " is already full health points"
                    << std::endl;
        return ;
    }
    if (this->_energy_points == 0)
    {
        std::cout << "No ressources to restore some health points"
                    << std::endl;
        return ;
    }
    std::cout << "ClapTrap "
                << this->_name
                << " has restored "
                << amount
                << " health points"
                << std::endl;
    this->_energy_points--;
    if (this->_hit_points + amount > 10)
        this->_hit_points = 10;
    else
        this->_hit_points += amount;
}



std::string ClapTrap::getName() const {
    return this->_name;
}