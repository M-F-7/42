/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/12 10:49:52 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"


Fixed::Fixed() : _nb_fixed(0) {
    std::cout << "Default constructor called"
                << std::endl;
}

Fixed::Fixed(const Fixed& other){
    std::cout << "Copy constructor called"
                << std::endl;
    this->_nb_fixed = other._nb_fixed;
}

Fixed& Fixed::operator=(const Fixed& other){
    std::cout << "Copy assignment operator called"
                << std::endl;
    if (this != &other)
        this->_nb_fixed = other._nb_fixed;
    return *this;
}

Fixed::~Fixed(){
    std::cout << "Destructor called"
                << std::endl;
}

int Fixed::getRawBits( void ) const{
    std::cout << "getRawBits member function called"
                << std::endl;
    return this->_nb_fixed;
}

void Fixed::setRawBits( int const raw ){
    this->_nb_fixed = raw;
}
