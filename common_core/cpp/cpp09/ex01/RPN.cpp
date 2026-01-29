/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:52:38 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/22 15:41:49 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"


bool is_operator(char c) {
    return std::string("+-*/").find(c) != std::string::npos;
}

double do_op(char c, double a, double b){
    if (c == '+')
        return a + b;
    else if (c == '-')
        return a - b;
    else if (c == '*')
        return a * b;
    else if (c == '/'){
        if (b == 0)
            throw Invalid();
        else 
            return a / b;
    }
    else
        throw Invalid();
}


std::list<double> fill_list(std::string arg){
    std::list<double> lst;
    std::istringstream iss(arg);
    std::string token;

    while(iss >> token){
        char *end_stod;
        
        if (std::isdigit(token[0]) && token.size() == 1){
            lst.push_back(strtod(token.c_str(), &end_stod));
            if (*end_stod)
                throw Invalid();
        }
        else if (is_operator(token[0]) && lst.size() > 1)
        {
            double b = lst.back();
            lst.pop_back();
            double a = lst.back();
            lst.pop_back();
            double res = do_op(token[0], a, b);
            lst.push_back(res);
        }
        else
            throw Invalid();
    }
    if (lst.size() != 1)
        throw Invalid();
    std::cout << lst.front() << std::endl;
    return lst;
}

const char* Invalid::what() const throw(){
    return "Error";
}