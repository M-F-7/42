/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongDog.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:02:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 12:57:16 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongDog.hpp"

WrongDog::WrongDog(){
    std::cout << "WrongDog default constructor called"
                << std::endl;
    this->type = "Dog";
}

WrongDog::WrongDog(const WrongDog& other){
    std::cout << "WrongDog copy constructor called"
                << std::endl;
    this->type = other.type; 
}

WrongDog& WrongDog::operator=(const WrongDog& other){
    std::cout << "WrongDog copy assignment operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->type = other.type; 
    return *this;
}

WrongDog::~WrongDog(){
    std::cout << "WrongDog destructor called"
                << std::endl;
}


void WrongDog::setType(const std::string& type) {
    this->type = type;
}

std::string WrongDog::getType() const {
    return this->type;
}

void WrongDog::makeSound() const {
    std::cout << "Meow Meow"
                << std::endl;
}