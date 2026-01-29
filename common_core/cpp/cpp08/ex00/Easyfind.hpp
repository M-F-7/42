/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:44:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/15 15:52:00 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>

class InvalidNb : public std::exception{
    public:
        const char* what() const throw();
};
class InvalidVector : public std::exception{
    public:
        const char* what() const throw();
};

template <typename T>

int easyfind(std::vector<T>& v, int nb);

#include "Easyfind.tpp"