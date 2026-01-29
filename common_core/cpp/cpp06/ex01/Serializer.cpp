/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:24:00 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/19 14:55:35 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer(){
    std::cout << "Serializer default constructor called"
                << std::endl;
}
    
Serializer::Serializer(const Serializer& other){
    std::cout << "Serializer copy constructor called"
                << std::endl;
    (void)other;
}
    
Serializer& Serializer::operator=(const Serializer& other){
    std::cout << "Serializer copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    return *this;
}

Serializer::~Serializer(){
    std::cout << "Serializer destructor called"
                << std::endl;
}

uintptr_t Serializer::serialize(Data* ptr){
    return reinterpret_cast<uintptr_t>(ptr);
}

Data* Serializer::deserialize(uintptr_t raw){
    return reinterpret_cast<Data*>(raw);
}