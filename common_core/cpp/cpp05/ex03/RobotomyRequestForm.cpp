/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:17:52 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/22 09:15:15 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"


RobotomyRequestForm::RobotomyRequestForm() : AForm("robotomy request", 72, 45), _target("default"){
    std::cout << "Robot default constructor called"
                << std::endl;
}
    
RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("robotomy request", 72, 45), _target(target){
    std::cout << "Robot param constructor called"
                << std::endl;       
}
    
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other) : AForm("robotomy request", 72, 45), _target(other._target){
    std::cout << "Robot copy constructor called"
                << std::endl;
}
    
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other){
    std::cout << "Robot copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    this->_target = other._target;
    return *this;
}
    
RobotomyRequestForm::~RobotomyRequestForm(){
    std::cout << "Robot destructor called"
                << std::endl;
}

void RobotomyRequestForm::execute(const Bureaucrat& executor) const {
    if (!this->getSigned())
        throw RobotomyRequestForm::FormNotSignedException();
    if (executor.getGrade() > this->getEgrade())
        throw AForm::GradeTooLowException();
        
    std::cout << "* DRILLING NOISES *" << std::endl;
    std::cout << "BZZZZZZT! BIM! BIM! BAM! BOW!" << std::endl;
    
    srand(time(NULL));
    if (!rand() % 2)
        std::cout << _target
                    << " has been robotomized successfully"
                    << std::endl;
    else
        std::cout << "The robotomy of "
                    << _target
                    << " failed"
                    << std::endl;
    
}

const char* RobotomyRequestForm::FormNotSignedException::what() const throw() {
    return "Can't sign the form";
}
