/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:52:21 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/14 22:07:13 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria(std::string const & type) : type(type){
    std::cout << "AMateria default constructor called"
                << std::endl;
}
    
AMateria::~AMateria(){
    std::cout << "AMateria destructor called"
                << std::endl;
}

AMateria::AMateria(const AMateria& other){
    std::cout << "AMateria copy constructor called"
                << std::endl;
    this->type = other.type;
}
    
AMateria& AMateria::operator=(const AMateria& other){
        std::cout << "AMateria copy assignement operator called"
                    << std::endl;
        if (this != &other)
            this->type = other.type;
        return *this;
}
    
    
std::string const & AMateria::getType() const{
            return this->type;
}

void AMateria::use(ICharacter& target) {
    (void)target;
}