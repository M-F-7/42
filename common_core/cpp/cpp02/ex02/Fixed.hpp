/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/12 10:19:14 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <stdbool.h>
#include <cmath> //on peut use roundf

class Fixed{

public:
    Fixed();
    Fixed(const Fixed& other);
    Fixed(const int integer);
    Fixed(const float nb_comma);
    ~Fixed();
    Fixed& operator=(const Fixed& other);
    bool operator<(const Fixed& fixed) const;
    bool operator>(const Fixed& fixed) const;
    bool operator>=(const Fixed& fixed) const;
    bool operator<=(const Fixed& fixed) const;
    bool operator==(const Fixed& fixed) const;
    bool operator!=(const Fixed& fixed) const;

    Fixed operator+(const Fixed& fixed) const;
    Fixed operator-(const Fixed& fixed) const;
    Fixed operator*(const Fixed& fixed) const;
    Fixed operator/(const Fixed& fixed) const;

    Fixed& operator++();
    Fixed operator++(int);
    Fixed& operator--();
    Fixed operator--(int);

    

    int getRawBits( void ) const;
    void setRawBits( int const raw );
    int toInt( void ) const;
    float toFloat( void ) const;

    static Fixed &    min(Fixed& n1, Fixed& n2);
    static Fixed const &   min(const Fixed& n1, const Fixed& n2);
    static Fixed &   max(Fixed& n1, Fixed& n2);
    static Fixed const &       max(const Fixed& n1, const Fixed& n2);

private:

    int _nb_fixed;
    static const int _nb_bits = 8;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);
std::ostream& operator<(std::ostream& os, const Fixed& fixed);
std::ostream& operator>(std::ostream& os, const Fixed& fixed);
std::ostream& operator>=(std::ostream& os, const Fixed& fixed);
std::ostream& operator<=(std::ostream& os, const Fixed& fixed);
std::ostream& operator==(std::ostream& os, const Fixed& fixed);
std::ostream& operator!=(std::ostream& os, const Fixed& fixed);

#endif 