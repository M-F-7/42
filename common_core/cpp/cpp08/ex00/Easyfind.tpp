/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Easyfind.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:28:25 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/21 19:26:58 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Easyfind.hpp"

template <typename T> int easyfind(std::vector<T>& v, int nb){
    if (v.empty())
        throw InvalidVector();
    for (size_t i = 0; i < v.size(); i++)
        if (v.at(i) == nb)
            return v.at(i);
    throw InvalidNb();
};

const char* InvalidNb::what() const throw() {
    return "Number not found in container";
}

const char* InvalidVector::what() const throw() {
    return "Invalid vector";
}