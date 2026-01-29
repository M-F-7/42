/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:05:11 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/14 21:02:12 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {
    std::cout << "Ice default constructor called"
                << std::endl;
                
}

Ice::Ice(const Ice& other) : AMateria("ice") {
    std::cout << "Ice copy constructor called"
                << std::endl;
    this->type = other.type;
}

Ice& Ice::operator=(const Ice& other){
    std::cout << "Ice copy assignement operator called"
                << std::endl;
    if (this != &other)
        this->type = other.type;
    return *this;
}

Ice::~Ice(){
    std::cout << "Ice destructor called"
                << std::endl;
}

AMateria* Ice::clone() const{
    return new Ice(*this);
}

void Ice::use(ICharacter& target) {
    std::cout << "* shoots an ice bolt at " 
                << target.getName() 
                << " *" 
                << std::endl;
}