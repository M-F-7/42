/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/11 22:50:00 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath> //on peut use roundf

class Fixed{

public:
    Fixed();
    Fixed(const Fixed& other);
    Fixed(const int integer);
    Fixed(const float nb_comma);
    Fixed& operator=(const Fixed& other);
    ~Fixed();

    int getRawBits( void ) const;
    void setRawBits( int const raw );
    int toInt( void ) const;
    float toFloat( void ) const;

private:

    int _nb_fixed;
    static const int _nb_bits = 8;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);


#endif 