/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:52:08 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/22 15:37:47 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <list>
#include <sstream>
#include <cstdlib>


class Invalid : public std::exception{
public:
    const char* what() const throw();
};

std::list<double> fill_list(std::string arg);
bool is_operator(char c);
double do_op(char c, double a, double b);