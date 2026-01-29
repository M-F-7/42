/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 20:57:00 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

Zombie::Zombie(){
    
}

Zombie::Zombie(std::string name) : name(name) {
    
}

Zombie::~Zombie(){
    
}

void    Zombie::announce(){
    
    std::cout << name 
                << ": BraiiiiiiinnnzzzZ..." 
                << std::endl;
}

void Zombie::setName(std::string name) {
    this->name = name;
}