/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:36:06 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/21 15:34:18 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : _signed(false), _sgrade(100), _egrade(1){
    std::cout << "Form default constructor called"
                << std::endl;
}

Form::Form(const std::string& name, int sgrade, int egrade) : _name(name), _signed(false), _sgrade(sgrade), _egrade(egrade) {
    std::cout << "Form param constructor called" 
                << std::endl;
    if (sgrade < 1 || egrade < 1)
        throw GradeTooHighException();
    if (sgrade > 150 || egrade > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& other): _name(other._name), _sgrade(other._sgrade), _egrade(other._egrade), _signed(other._signed){
    std::cout << "Form copy constructor called"
                << std::endl;
}

Form& Form::operator=(const Form& other){
    if (this == &other)
        return *this;

    this->_signed = other._signed;
    
    std::cout << "Form copy assignement operator called"
                << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Name: "
        << f.getName()
        << ", Form sgrade: " 
        << f.getSgrade()
        << ", Form egrade: "
        << f.getEgrade()
        << ", Actual status signed: "
        << f.getSigned()
        << std::endl;
    return os;
}

Form::~Form(){
    std::cout << "Form destructor called"
                << std::endl;
}


const std::string Form::getName() const{
        return this->_name;
}
    
bool Form::getSigned() const{
        return this->_signed;
}


int Form::getSgrade() const{
        return this->_sgrade;
}


int Form::getEgrade() const{
        return this->_egrade;
}

const char* Form::GradeTooHighException::what() const throw() {
    return "Form Grade too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Form Grade too low!";
}


void Form::beSigned(Bureaucrat& b){
    if (b.getGrade() > _sgrade)
        throw Form::GradeTooLowException();
    this->_signed = true;
}