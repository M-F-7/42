/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:24:16 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/20 16:44:58 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma  once

#include  <iostream>
#include <limits.h>
#include <cstdlib>
#include <iomanip>
#include <climits>
#include <limits>
#include <cmath>
#include <cfloat>
#include <cstddef>
#include <cerrno>

class  ScalarConverter{

public:
    
    static void Convert(std::string arg);
private:
    ScalarConverter();
    ScalarConverter(ScalarConverter& other);
    ScalarConverter&  operator=(ScalarConverter& other);
    ~ScalarConverter();


};

bool IsValidInt(std::string arg);
bool IsValidDouble(std::string arg);
bool IsValidFloat(std::string arg);
bool CheckLimits(std::string arg);

void printInt(int i, bool integer);
void printDouble(double d, bool integer, bool in_limits);
void printChar(char c, bool integer);
void printFloat(float f, bool integer, bool in_limits);

void printNan();
void printFloatInf(float f);
void printDoubleInf(double d);
