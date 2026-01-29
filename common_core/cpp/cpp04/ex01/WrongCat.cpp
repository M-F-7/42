/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongWrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:17:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/13 13:54:48 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(){
    std::cout << "WrongCat default constructor called"
                << std::endl;
    this->type = "Cat";
}

WrongCat::WrongCat(const WrongCat& other){
    std::cout << "WrongCat copy constructor called"
                << std::endl;
    this->type = other.type; 
}

WrongCat& WrongCat::operator=(const WrongCat& other){
    std::cout << "WrongCat copy assignment operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->type = other.type; 
    return *this;
}

WrongCat::~WrongCat(){
    std::cout << "WrongCat destructor called"
                << std::endl;
}


void WrongCat::setType(const std::string& type) {
    this->type = type;
}

std::string WrongCat::getType() const {
    return this->type;
}

void WrongCat::makeSound() const {
    std::cout << "Meow Meow"
                << std::endl;
}