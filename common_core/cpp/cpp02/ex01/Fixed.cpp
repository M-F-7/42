/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/11 22:49:42 by mfernand         ###   ########.fr       */
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

Fixed::Fixed(const int integer){
    std::cout << "Int constructor called"
                << std::endl;
    this->_nb_fixed = integer << _nb_bits;
}

Fixed::Fixed(const float nb_comma){
    std::cout << "Float constructor called"
                << std::endl;
    this->_nb_fixed = roundf(nb_comma * (1 << _nb_bits));
}

Fixed& Fixed::operator=(const Fixed& other){
    std::cout << "Copy assignment operator called"
                << std::endl;
    if (this != &other)
        this->_nb_fixed = other._nb_fixed;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;
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

int Fixed::toInt( void ) const{
    return this->_nb_fixed >> _nb_bits;
}

float Fixed::toFloat( void ) const{
    return static_cast<float>(this->_nb_fixed) / (1 << _nb_bits);
}