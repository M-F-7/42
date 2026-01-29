/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:25:00 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/15 15:16:55 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"



int main() {
    std::cout << "=== Testing Form Creation ===" << std::endl;
    
    Bureaucrat lowGrade("A", 150);
    Bureaucrat midGrade("B", 50);
    Bureaucrat highGrade("C", 1);
    
    std::cout << lowGrade << std::endl;
    std::cout << midGrade << std::endl;
    std::cout << highGrade << std::endl;
    
    std::cout << "\n=== Testing ShrubberyCreationForm ===" << std::endl;
    ShrubberyCreationForm shrub("home");
    std::cout << shrub << std::endl;
    
    // Test signing with low grade (should fail)
    lowGrade.signForm(shrub);
    
    // Test signing with sufficient grade
    midGrade.signForm(shrub);
    
    // Test execution without signing
    ShrubberyCreationForm shrub2("garden");
    midGrade.executeForm(shrub2);
    
    // Test execution with signing
    midGrade.executeForm(shrub);
    
    std::cout << "\n=== Testing RobotomyRequestForm ===" << std::endl;
    RobotomyRequestForm robot("Bender");
    std::cout << robot << std::endl;
    
    // Test with insufficient grade for signing
    lowGrade.signForm(robot);
    
    // Test with sufficient grade for signing
    midGrade.signForm(robot);
    
    // Test execution with insufficient grade
    lowGrade.executeForm(robot);
    
    // Test execution with sufficient grade
    Bureaucrat robotExecutor("RobotMaster", 40);
    robotExecutor.signForm(robot);
    robotExecutor.executeForm(robot);
    
    std::cout << "\n=== Testing PresidentialPardonForm ===" << std::endl;
    PresidentialPardonForm pardon("Criminal");
    std::cout << pardon << std::endl;
    
    // Test with insufficient grade
    midGrade.signForm(pardon);
    
    // Test with sufficient grade
    highGrade.signForm(pardon);
    highGrade.executeForm(pardon);
    
    std::cout << "\n=== Testing Exception Handling ===" << std::endl;
    try {
        PresidentialPardonForm pardon2("Another Criminal");
        // Try to execute without signing
        highGrade.executeForm(pardon2);
    } catch (std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    std::cout << "\n=== Testing Intern ===" << std::endl;
    Intern intern;
    AForm* form1;
    AForm* form2;
    AForm* form3;
    AForm* form4;
    
    // Test valid form creation
    std::cout << "\n--- Testing valid forms ---" << std::endl;
    form1 = intern.makeForm("shrubbery creation", "garden");
    if (form1) {
        std::cout << *form1 << std::endl;
        highGrade.signForm(*form1);
        highGrade.executeForm(*form1);
        delete form1;
    }
    
    form2 = intern.makeForm("robotomy request", "Marvin");
    if (form2) {
        std::cout << *form2 << std::endl;
        highGrade.signForm(*form2);
        highGrade.executeForm(*form2);
        delete form2;
    }
    
    form3 = intern.makeForm("presidential pardon", "Ford Prefect");
    if (form3) {
        std::cout << *form3 << std::endl;
        highGrade.signForm(*form3);
        highGrade.executeForm(*form3);
        delete form3;
    }
    
    // Test invalid form creation
    std::cout << "\n--- Testing invalid form ---" << std::endl;
    form4 = intern.makeForm("unknown form", "target");
    if (!form4) {
        std::cout << "Form creation failed as expected" << std::endl;
    }
    
    std::cout << "\n=== End of tests ===" << std::endl;
    return 0;
}