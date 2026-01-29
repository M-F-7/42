/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:19:22 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 12:51:18 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("unedfined"){
    std::cout << "Animal default constructor called"
                << std::endl;
}

Animal::Animal(const Animal& other){
    std::cout << "Animal copy constructor called"
                << std::endl;
    this->type = other.type;        
}

Animal& Animal::operator=(const Animal& other){
    std::cout << "Animal copy assignment operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->type = other.type;
    return *this;  
}

Animal::~Animal(){
    std::cout << "Animal destructor called"
                << std::endl;
}

void Animal::makeSound() const {
    std::cout << "Grrrrrrrrrrr"
                << std::endl;
}

void Animal::setType(const std::string& type) {
    this->type = type;
}

std::string Animal::getType() const {
    return this->type;
}