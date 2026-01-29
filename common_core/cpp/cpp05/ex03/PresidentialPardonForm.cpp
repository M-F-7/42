/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:36:53 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/22 09:16:31 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"


PresidentialPardonForm::PresidentialPardonForm() : AForm("presidential pardon", 25, 5), _target("default"){
    std::cout << "President default constructor called"
                << std::endl;
}
    
PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("presidential pardon", 25, 5), _target(target){
    std::cout << "President param constructor called"
                << std::endl;       
}
    
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) : AForm("presidential pardon", 25, 5), _target(other._target){
    std::cout << "President copy constructor called"
                << std::endl;
}
    
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other){
    std::cout << "President copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->_target = other._target;
    return *this;
}
    
PresidentialPardonForm::~PresidentialPardonForm(){
    std::cout << "President destructor called"
                << std::endl;
}

void PresidentialPardonForm::execute(const Bureaucrat& executor) const {
    if (!this->getSigned())
        throw PresidentialPardonForm::FormNotSignedException();
    if (executor.getGrade() > this->getEgrade())
        throw AForm::GradeTooLowException();
        
    std::cout << _target
                << " has been pardonned by Zaphod Beeblebrox."
                << std::endl;
    
}

const char* PresidentialPardonForm::FormNotSignedException::what() const throw() {
    return "Can't sign the form";
}