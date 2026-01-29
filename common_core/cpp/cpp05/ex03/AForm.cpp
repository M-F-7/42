/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:36:06 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/21 15:44:43 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm() : _signed(false), _sgrade(100), _egrade(1){
    std::cout << "AForm default constructor called"
                << std::endl;
}

AForm::AForm(const std::string& name, int sgrade, int egrade) : _name(name), _signed(false), _sgrade(sgrade), _egrade(egrade) {
    std::cout << "AForm param constructor called" 
                << std::endl;
    if (sgrade < 1 || egrade < 1)
        throw GradeTooHighException();
    if (sgrade > 150 || egrade > 150)
        throw GradeTooLowException();
}

AForm& AForm::operator=(const AForm& other){
    if (this == &other)
        return *this;

    this->_signed = other._signed;
    
    std::cout << "AForm copy assignement operator called"
                << std::endl;
    return *this;
}

AForm::AForm(const AForm& other): _name(other._name), _signed(other._signed), _sgrade(other._sgrade), _egrade(other._egrade){
    std::cout << "AForm copy constructor called"
                << std::endl;
}

std::ostream& operator<<(std::ostream& os, const AForm& f) {
    os << "Name: "
        << f.getName()
        << ", AForm sgrade: " 
        << f.getSgrade()
        << ", AForm egrade: "
        << f.getEgrade()
        << ", Actual status signed: "
        << f.getSigned()
        << std::endl;
    return os;
}

AForm::~AForm(){
    std::cout << "AForm destructor called"
                << std::endl;
}


const std::string AForm::getName() const{
        return this->_name;
}
    
bool AForm::getSigned() const{
        return this->_signed;
}


int AForm::getSgrade() const{
        return this->_sgrade;
}


int AForm::getEgrade() const{
        return this->_egrade;
}

const char* AForm::GradeTooHighException::what() const throw() {
    return "AForm Grade too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "AForm Grade too low!";
}

void AForm::beSigned(Bureaucrat& b) {
    if (b.getGrade() > _sgrade)
        throw AForm::GradeTooLowException();
    this->_signed = true;
}