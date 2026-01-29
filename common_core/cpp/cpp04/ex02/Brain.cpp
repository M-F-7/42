/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:07:25 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 12:51:13 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(){
    std::cout << "Brain default constructor called"
                << std::endl;
}

Brain::Brain(const Brain& other){
    std::cout << "Brain copy constructor called"
                << std::endl;
    for (int i = 0; i < 100; ++i) {
        this->ideas[i] = other.ideas[i];
    }
}
    
Brain& Brain::operator=(const Brain& other){
    std::cout << "Brain assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    for (int i = 0; i < 100; ++i) {
        this->ideas[i] = other.ideas[i];
    }
    return *this;
}

Brain::~Brain() {
    std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int index, const std::string& idea) {
    if (index >= 0 && index < 100)
        ideas[index] = idea;
}

std::string Brain::getIdea(int index) const {
    if (index >= 0 && index < 100)
        return ideas[index];
    return "";
}