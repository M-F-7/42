/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:44:40 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/15 15:15:09 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(){
    
    try {
        Bureaucrat foo("foo", 50);
        Form       bar("bar", 100, 1);

        std::cout << foo << std::endl;
        std::cout << bar << std::endl;

        foo.signForm(bar);
        std::cout << "Form signed status: " << bar.getSigned() << std::endl;

        Bureaucrat low("low", 120);
        Form hard("hard", 100, 100);
        low.signForm(hard);

        // Form bad("bad", 0, 100); // MUST give an exception

        // Bureaucrat badB("badB", 151); // MUST give an exception

        foo.incrementGrade();
        std::cout << "foo grade after increment: " << foo.getGrade() << std::endl;
        foo.decrementGrade();
        std::cout << "foo grade after decrement: " << foo.getGrade() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " 
                    << e.what() 
                    << std::endl;
    }
    return 0;
}