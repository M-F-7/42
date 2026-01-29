/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:23:40 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/19 15:32:06 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

int main() {

    // srand(static_cast<unsigned int>(std::time(NULL))); conversion explicit
    srand(time(NULL)); //implicit
    
    std::cout << "-----------------------------------"
                << std::endl;
                
    std::cout << "First  example:"
                << std::endl;
            
    std::cout << "-----------------------------------"
                << std::endl;
                
    Base* ptr = Base().generate();
    // Base* ptr = Base::generate();// if generate is static 
    ptr->identify(ptr);
    ptr->identify(*ptr);

    std::cout << "-----------------------------------"
                << std::endl;
                
    std::cout << "Second  example:"
                << std::endl;
            
    std::cout << "-----------------------------------"
                << std::endl;
    
    Base* ptr1 = Base().generate();
    // Base* ptr1 = Base::generate();
    ptr1->identify(ptr1);
    ptr1->identify(*ptr1);

    std::cout << "-----------------------------------"
                << std::endl;
                
    std::cout << "Last  example:"
                << std::endl;
            
    std::cout << "-----------------------------------"
                << std::endl;

    Base* ptr2 = Base().generate();
    // Base* ptr2 = Base::generate();
    ptr2->identify(ptr2);
    ptr2->identify(*ptr2);

    std::cout << "-----------------------------------"
                << std::endl;
                
    delete ptr, delete ptr1, delete ptr2;
    return 0;
}