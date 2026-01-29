/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:44:35 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/19 21:43:21 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"


Bureaucrat::Bureaucrat(){
    std::cout << "Bureaucrat default constructor called" 
    << std::endl;
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name), _grade(grade){
    if (grade < 1)
        throw GradeTooHighException();
    if (grade > 150)
        throw GradeTooLowException();
    std::cout << "Bureaucrat name and grade constructor called" 
    << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other._name), _grade(other._grade) {
    std::cout << "Bureaucrat copy constructor called"
                << std::endl;
}

Bureaucrat::~Bureaucrat(){
    std::cout << "Bureaucrat destructor called"
                << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other){
    
    if (this == &other)
        return *this;
    this->_grade = other._grade;
    std::cout << "Bureaucrat copy assignment operator called"
                << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b) {
    os << b.getName()
        << ", bureaucrat grade " 
        << b.getGrade();
    return os;
}
    
const std::string& Bureaucrat::getName() const{
    return this->_name;
}
    
int Bureaucrat::getGrade() const{
    return this->_grade;        
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return "Grade too high!";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return "Grade too low!";
}

void Bureaucrat::incrementGrade() {
    if (_grade - 1 < 1)
        throw GradeTooHighException();
    _grade--;
}

void Bureaucrat::decrementGrade() {
    if (_grade + 1 > 150)
        throw GradeTooLowException();
    _grade++;
}