/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:36:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/21 13:51:05 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <stdbool.h>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm{

private:
    const std::string _name;
    bool    _signed;
    const int _sgrade;
    const int _egrade;
    
public:
    AForm();
    AForm(const std::string& name, int sgrade, int egrade);
    AForm(const AForm& other);
    AForm& operator=(const AForm& other);
    virtual ~AForm();

    const std::string getName() const;
    bool getSigned() const;
    int getSgrade() const;
    int getEgrade() const;

    virtual void beSigned(Bureaucrat& b); //It changes the Aform’s status to signed if the bureaucrat’s grade is high enough(greater than or equal to the required one). Remember, grade 1 is higher than grade 2. If the grade is too low, throw a AForm::GradeTooLowException.
    virtual void execute(const Bureaucrat& executor) const = 0;
    class GradeTooHighException: public std::exception{
        public:
            const char* what() const throw();
            
    };
    class GradeTooLowException: public std::exception{
        public:
            const char* what() const throw();
            
    };
};

std::ostream& operator<<(std::ostream& os, const AForm& f);