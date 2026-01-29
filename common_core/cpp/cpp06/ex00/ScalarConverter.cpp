/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:24:21 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/20 18:47:36 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"



ScalarConverter::ScalarConverter() {
    std::cout << "ScalarConverter default construtor  called"
                << std::endl;
}
    
    
ScalarConverter::ScalarConverter(ScalarConverter& other) {
    std::cout << "ScalarConverter copy constructor called"
                << std::endl;
    (void)other;
}
    
    
ScalarConverter& ScalarConverter::operator=(ScalarConverter& other) {
    std::cout << "ScalarConverter copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    return *this;
}
    
    
ScalarConverter::~ScalarConverter() {
    std::cout << "ScalarConverter destructor called"
                <<  std::endl;
}

void ScalarConverter::Convert(std::string arg){
    
    if (arg == "nanf" || arg == "nan") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
        return;
    }
    
    if (arg == "+inff" || arg == "+inf") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
        return;
    }
    
    if (arg == "-inff" || arg == "-inf") {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
        return;
    }

    
    //SIMPLE CHAR
    if (arg.size() == 1 && std::isprint(arg[0]) && !std::isdigit(arg[0])) {
        char c = arg[0];
        std::cout << "char: " << c << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
        return;
    }
    
    errno = 0;
    char* endptr;
    double d = strtod(arg.c_str(), &endptr);

    if (std::isnan(d)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
        return;
    }
    
    if (std::isinf(d)) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        if (d > 0) {
            std::cout << "float: +inff" << std::endl;
            std::cout << "double: +inf" << std::endl;
        } else {
            std::cout << "float: -inff" << std::endl;
            std::cout << "double: -inf" << std::endl;
        }
        return;
    }

    
    if (errno == ERANGE || (*endptr != '\0' && *endptr != 'f'))
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return ;
    }

    std::cout << std::fixed << std::setprecision(1);

    //CHAR
    if (d >= 32 && d <= 126)
        std::cout << "char: " << static_cast<char>(d) << std::endl;
    else if (d >= 0 && d <= 127)
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: impossible" << std::endl;

    //int 
    if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;


    //float

    if (d < -std::numeric_limits<float>::max() || d > std::numeric_limits<float>::max())
        std::cout << "float: impossible" << std::endl;
    else
        std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;


    //double
    std::cout << "double: " << d << std::endl;
}