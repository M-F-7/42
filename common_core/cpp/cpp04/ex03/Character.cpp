/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:13:44 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 12:49:54 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

//  Dans le cas où on essaie d’ajouter une
// Materia à un inventaire plein, ou d’utiliser/retirer une Materia qui n’existe pas, ne faites
// rien (cela n’autorise pas les bugs pour autant)

Character::Character() {
    for (int i = 0; i < 4; i++)
        _inventory[i] = NULL;
    std::cout << "Character default constructor called" << std::endl;
}

Character::Character(const std::string name) : _name(name) {
    for (int i = 0; i < 4; i++)
        _inventory[i] = NULL;
    std::cout << "Character with name constructor called" << std::endl;
}

Character::Character(const Character& other){
    std::cout << "Character copy constructor called"
                << std::endl;
    this->_name = other._name;
    for (int i = 0; i < 4; i++) {
        if (other._inventory[i])
            _inventory[i] = other._inventory[i]->clone();
        else
            _inventory[i] = NULL;
    }
    
}

Character& Character::operator=(const Character& other){
    std::cout << "Character copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->_name = other._name;
    for (int i = 0; i < 4; i++) {
        if (_inventory[i])
            delete _inventory[i];
        if (other._inventory[i])
            _inventory[i] = other._inventory[i]->clone();
        else
            _inventory[i] = NULL;
    }
    return *this;
    
}

Character::~Character(){
    for (int i = 0; i < 4; i++)
        if (this->_inventory[i])
            delete _inventory[i];
    std::cout << "Character destructor called"
                << std::endl;
}


 std::string const & Character::getName() const{
    return this->_name;
 }
 
    
void Character::equip(AMateria* m){
    
    if (!m)
        return;
    for (int i = 0; i < 4; i++)
    {
        if (!this->_inventory[i])
        {
           this->_inventory[i] = m;
            return;
        }            
    }
}


void Character::unequip(int idx){           //La fonction membre unequip() ne doit PAS delete la Materia !
    if (idx < 0 || idx > 3)
        return ;
    if (!this->_inventory[idx])
        return ;
    if (this->_inventory[idx])
        this->_inventory[idx] = NULL;
        
}
    

void Character::use(int idx, ICharacter& target){
    if (idx < 0 || idx > 3)
        return ;
    if (!this->_inventory[idx])
        return ;
    if (this->_inventory[idx])
        this->_inventory[idx]->use(target);
}