/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:11:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 21:42:03 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Weapon.hpp"

Weapon::Weapon(){
    
}

Weapon::Weapon(const std::string& type) : type(type) {
    
}

Weapon::~Weapon(){

}


const  std::string& Weapon::getType() const{
    return this->type;
}

void Weapon::setType(const std::string& type){
    this->type = type;
}