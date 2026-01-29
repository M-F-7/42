/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:44:40 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/19 21:34:27 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(){
    
    try {
        Bureaucrat foo("foo", 1);
        Bureaucrat bar("bar", 150);

        std::cout << "Name: "
                  << foo.getName()
                  << ", Grade: "
                  << foo.getGrade()
                  << std::endl;

        std::cout << "Name: "
                  << bar.getName()
                  << ", Grade: "
                  << bar.getGrade()
                  << std::endl;

        foo.incrementGrade();
        bar.decrementGrade();

        foo = bar;
        foo.incrementGrade();

        std::cout << "Name: "
                  << foo.getName()
                  << ", Grade: "
                  << foo.getGrade()
                  << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " 
                    << e.what() 
                    << std::endl;
    }
    return 0;
}