/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:37:25 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/21 15:24:14 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AForm.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

class AForm;

class RobotomyRequestForm : public AForm{

public:
    RobotomyRequestForm();
    RobotomyRequestForm(std::string target);
    RobotomyRequestForm(const RobotomyRequestForm& other);
    RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
    ~RobotomyRequestForm();

    void execute(const Bureaucrat& executor) const;

    class FormNotSignedException: public std::exception{
        public:
            const char* what() const throw();
    };

private:
    std::string _target;
};