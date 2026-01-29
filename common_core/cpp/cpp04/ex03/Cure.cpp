/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:05:06 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/14 21:02:04 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure") {
    std::cout << "Cure default constructor called"
                << std::endl;
                
}

Cure::Cure(const Cure& other) : AMateria ("cure") {
    std::cout << "Cure copy constructor called"
                << std::endl;
    this->type = other.type;
}

Cure& Cure::operator=(const Cure& other){
    std::cout << "Cure copy assignement operator called"
                << std::endl;
    if (this != &other)
        this->type = other.type;
    return *this;
}

Cure::~Cure(){
    std::cout << "Cure destructor called"
                << std::endl;
}

AMateria* Cure::clone() const{
    return new Cure(*this);
}

void Cure::use(ICharacter& target) {
    std::cout << "* heals " 
                << target.getName()
                << "'s wounds *"
                << std::endl;
}