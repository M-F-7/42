/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:16:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 12:56:42 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(){
    std::cout << "Dog default constructor called"
                << std::endl;
    this->type = "Dog";
    _Brain = new Brain();
}

Dog::Dog(const Dog& other){
    std::cout << "Dog copy constructor called"
                << std::endl;
    this->type = other.type; 
    this->_Brain = new Brain(*other._Brain);
}

Dog& Dog::operator=(const Dog& other){
    std::cout << "Dog copy assignment operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->type = other.type;
    if (this->_Brain)
        delete this->_Brain;
    this->_Brain = new Brain(*other._Brain);
    return *this;
}

Dog::~Dog(){
    std::cout << "Dog destructor called"
                << std::endl;
    delete _Brain;
}

void Dog::setType(const std::string& type) {
    this->type = type;
}

std::string Dog::getType() const {
    return this->type;
}

void Dog::makeSound() const {
    std::cout << "Wouf Wouf" 
                << std::endl;
}

void Dog::setBrain(Brain* brain) {
    if (_Brain)
        delete _Brain;
    _Brain = brain;
}

Brain* Dog::getBrain() const {
    return _Brain;
}