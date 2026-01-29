/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:16:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 12:51:36 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(){
    std::cout << "Cat default constructor called"
                << std::endl;
    this->type = "Cat";
}

Cat::Cat(const Cat& other){
    std::cout << "Cat copy constructor called"
                << std::endl;
    this->type = other.type; 
}

Cat& Cat::operator=(const Cat& other){
    std::cout << "Cat copy assignment operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->type = other.type; 
    return *this;
}

Cat::~Cat(){
    std::cout << "Cat destructor called"
                << std::endl;
}


void Cat::setType(const std::string& type) {
    this->type = type;
}

std::string Cat::getType() const {
    return this->type;
}

void Cat::makeSound() const {
    std::cout << "Meow Meow"
                << std::endl;
}