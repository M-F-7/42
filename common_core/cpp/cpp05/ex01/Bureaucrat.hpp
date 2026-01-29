/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:44:37 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/21 12:30:22 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <Form.hpp>

class Form;

class Bureaucrat{
  
private:
    const std::string _name;
    int               _grade;
    
public:
    Bureaucrat();
    Bureaucrat(const Bureaucrat &other);
    Bureaucrat(const std::string& _name, int _grade);
    ~Bureaucrat();
    Bureaucrat& operator=(const Bureaucrat& other);
    const std::string& getName() const;
    int getGrade() const;

    void incrementGrade();
    void decrementGrade();
    void signForm(Form& form);
    class GradeTooHighException: public std::exception{
        public:
            const char* what() const throw();
            
    };
    class GradeTooLowException: public std::exception{
        public:
            const char* what() const throw();
            
    };

};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& b);