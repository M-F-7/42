/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:08:21 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/14 22:09:02 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Animal{

public :
    Animal& operator=(const Animal& other);
    virtual ~Animal();
    
    virtual void    makeSound() const = 0;
    void setType(const std::string& type);
    std::string getType() const;
private :

protected :
    Animal();
    Animal(const Animal& other);
    std::string type;
};