/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:59:25 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/22 09:27:21 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

    
Intern::Intern(){
    std::cout << "Intern default constructor called"
                << std::endl;
}

Intern::Intern(const Intern& other){
    (void)other;
    std::cout << "Intern copy constructor called"
                << std::endl;
}
    
Intern& Intern::operator=(const Intern& other){
    std::cout << "Intern copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    return *this;
}
    
Intern::~Intern(){
    std::cout << "Intern destructor called"
                << std::endl;
}


AForm* Intern::makeForm(std::string form_name, std::string target_name){
    
    std::string tab[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    for (int i = 0; i < 3; i++){
        if (form_name == tab[i]){
            switch(i){
                
                    case 0:
                        std::cout << "Intern creates " << form_name << std::endl;
                        return new ShrubberyCreationForm(target_name);
                    case 1:
                        std::cout << "Intern creates " << form_name << std::endl;
                        return new RobotomyRequestForm(target_name);
                    case 2:
                        std::cout << "Intern creates " << form_name << std::endl;
                        return new PresidentialPardonForm(target_name);
                    default :
                        std::cout << "Intern cannot create " 
                                    << form_name 
                                    << " form" 
                                    << std::endl;
            }
        }
    }
    return NULL;
}
