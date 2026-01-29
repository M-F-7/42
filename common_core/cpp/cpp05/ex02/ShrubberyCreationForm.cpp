/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:56:13 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/22 09:17:38 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"


ShrubberyCreationForm::ShrubberyCreationForm() :  AForm("shrubbery creation", 145, 137), _target("default"){
    std::cout << "Shrubb default constructor called"
                << std::endl;
}
    
ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("shrubbery creation", 145, 137), _target(target){
    std::cout << "Shrubb param constructor called"
                << std::endl;       
}
    
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other) : AForm("shrubbery creation", 145, 137), _target(other._target){
    std::cout << "Shrubb copy constructor called"
                << std::endl;
}
    
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other){
    std::cout << "Shrubb copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->_target = other._target;
    return *this;
}
    
ShrubberyCreationForm::~ShrubberyCreationForm(){
    std::cout << "Shrubb destructor called"
                << std::endl;
}

void ShrubberyCreationForm::execute(const Bureaucrat& executor) const {
    if (!this->getSigned())
        throw ShrubberyCreationForm::FormNotSignedException();
    if (executor.getGrade() > this->getEgrade())
        throw AForm::GradeTooLowException();

    std::ofstream ofs;
    ofs.open((_target + "_shrubbery").c_str());
    if (!ofs)
        throw std::runtime_error("Failed to open file");

    ofs << "       _-_\n"
           "    /~~   ~~\\\n"
           " /~~         ~~\\\n"
           "{               }\n"
           " \\  _-     -_  /\n"
           "   ~  \\\\ //  ~\n"
           "_- -   | | _- _\n"
           "  _ -  | |   -_\n"
           "      // \\\\\n";
    ofs.close();
}


const char* ShrubberyCreationForm::FormNotSignedException::what() const throw() {
     return "Form is not signed";
}
