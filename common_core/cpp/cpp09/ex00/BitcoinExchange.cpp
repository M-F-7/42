/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:28:25 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/22 14:13:37 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::multimap<std::string, double> fill_db(){
     std::multimap<std::string, double> db;
    
    std::ifstream infile("data.csv");
    if (!infile)
        return std::cerr << "Problem when opening the infile" 
                            << std::endl, db;
    std::string line;
    size_t pos = 0;
    bool first_line = true;
    while(std::getline(infile, line)){
        if (first_line){
            first_line = false;
            continue;
        }
        pos = line.find(',', 0);
        if (pos != std::string::npos)
            db.insert(std::make_pair(line.substr(0, pos), std::strtod(line.substr(pos + 1).c_str(), NULL)));
    }
    return db;
    
}

std::multimap<std::string, double> fill_input(std::string arg, std::multimap<std::string, double> db){
    std::multimap<std::string, double> input;
    
    std::ifstream infile(arg.c_str());
    if (!infile)
        return std::cerr << "Problem when opening the infile" 
                            << std::endl, input;

    std::string line;
    size_t pos = 0;
    bool first_line = true;
    
    while(std::getline(infile, line)){
        if (first_line){
            first_line = false;
            continue;
        }
        pos = line.find('|', 0);
        if (pos == std::string::npos)
            std::cerr << "Error: bad input => " << line << std::endl;
        else if (pos > 0){
            std::string key = line.substr(0, pos - 1);
            double value = std::strtod(line.substr(pos + 2).c_str(), NULL);
            
    
            input.insert(std::make_pair(key, value));
            if (parse_date(key) && parse_value(value)){
                std::multimap<std::string, double>::iterator found = db.upper_bound(key); // equal to the db key closest > input key
                if (found != db.begin()){
                    --found; // take the same date or the little one before the input date
                    std::cout << key << " => " << value << " = " << value * found->second << std::endl;
                }
            }
        }
    }
    return input;
}

bool parse_date(const std::string date){
    bool error = false;
    for (size_t i = 0; i < date.size(); i++){
        if (i == 4 || i == 7){
            if (date[i] != '-')
                error = true;
        }
        else if (!std::isdigit(date[i]))
            error = true;
    }
    int year = std::atoi(date.substr(0, 4).c_str());
    if (year < 2009 || year > 2025)
        error = true;
        
    int month = std::atoi(date.substr(5, 2).c_str());
    if (month < 1 || month > 12)
        error = true;
        
    int day = std::atoi(date.substr(8, 2).c_str());
    if (day < 1 || day > 31) //not depending about month
        error = true;
    
    if (error)
        return false;
    return true;
}


bool parse_value(double nb){
    if (nb < 0)
        return std::cerr << "Error: not a positive number." << std::endl, false;
    else if (nb > 1000)
        return std::cerr << "Error: too large a number." << std::endl, false;
    return true;
}