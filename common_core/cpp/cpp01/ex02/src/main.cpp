/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 21:24:43 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(){

    std::string brain =  "HI THIS IS BRAIN";
    std::string *ptr = &brain;
    std::string &ref = brain;

    std::cout << "The memory address of the string variable: "
                << &brain 
                << std::endl;
    

    std::cout << "The memory address held by stringPTR: "
                << ptr 
                << std::endl;
    
    
    std::cout << "The memory address held by stringREF: "
                << &ref 
                << std::endl;
                
    std::cout << "The value of the string variable: "
                << brain 
                << std::endl;

                
    std::cout << "The value pointed to by stringPTR: "
                << *ptr 
                << std::endl;

                
    std::cout << "The value pointed to by stringREF: "
                << ref 
                << std::endl;
    return (0);
}
