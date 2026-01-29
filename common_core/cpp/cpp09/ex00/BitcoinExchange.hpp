/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:44:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/22 14:00:32 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <map>
#include <fstream>
#include <stdlib.h>

std::multimap<std::string, double> fill_db();
std::multimap<std::string, double> fill_input(std::string arg, std::multimap<std::string, double> db);

bool valid_line(std::string line,bool first_line);

void parse_input(std::multimap<std::string, double> db, std::multimap<std::string, double> input);
bool parse_date(const std::string date);
bool parse_value(double nb);