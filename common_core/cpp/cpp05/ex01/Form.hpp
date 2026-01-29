/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:36:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/21 12:26:27 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdbool.h>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form{

private:
    const std::string _name;
    bool    _signed;
    const int _sgrade;
    const int _egrade;
    
public:
    Form();
    Form(const std::string& name, int sgrade, int egrade);
    Form(const Form& other);
    Form& operator=(const Form& other);
    ~Form();

    const std::string getName() const;
    bool getSigned() const;
    int getSgrade() const;
    int getEgrade() const;

    void beSigned(Bureaucrat& b); //It changes the form’s status to signed if the bureaucrat’s grade is high enough(greater than or equal to the required one). Remember, grade 1 is higher than grade 2. If the grade is too low, throw a Form::GradeTooLowException.
    class GradeTooHighException: public std::exception{
        public:
            const char* what() const throw();
            
    };
    class GradeTooLowException: public std::exception{
        public:
            const char* what() const throw();
            
    };
};

std::ostream& operator<<(std::ostream& os, const Form& f);