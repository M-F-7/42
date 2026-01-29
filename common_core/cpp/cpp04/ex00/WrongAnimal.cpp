/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:18:37 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/13 13:53:55 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("unedfined"){
    std::cout << "WrongAnimal default constructor called"
                << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other){
    std::cout << "WrongAnimal copy constructor called"
                << std::endl;
    this->type = other.type;        
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other){
    std::cout << "WrongAnimal copy assignment operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->type = other.type;
    return *this;  
}

WrongAnimal::~WrongAnimal(){
    std::cout << "WrongAnimal destructor called"
                << std::endl;
}

void WrongAnimal::makeSound() const {
    std::cout << "Grrrrrrrrrrr"
                << std::endl;
}

void WrongAnimal::setType(const std::string& type) {
    this->type = type;
}

std::string WrongAnimal::getType() const {
    return this->type;
}