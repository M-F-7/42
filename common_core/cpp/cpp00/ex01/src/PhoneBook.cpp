/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:33:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 12:22:09 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp"
#include "../include/Contact.hpp"

PhoneBook::PhoneBook(): nb_contacts(0){
    
}

PhoneBook::~PhoneBook(){

}

void PhoneBook::addContact(){
    
    static int total_contacts = 0;
    contacts[nb_contacts].fillContact();
    if (contacts[nb_contacts].isSaved())
    {
        if (total_contacts < 8)
            total_contacts++;
        this->current_count = total_contacts;
        nb_contacts = (nb_contacts + 1) % 8;
    }
}   

void PhoneBook::searchContact(){

    if (nb_contacts == 0)
    {
        std::cout << "Need one contact" << std::endl;
        return ;
    }
    std::cout << "|     INDEX|FIRST NAME| LAST NAME|  NICKNAME|" << std::endl;
    for (int i = 0; i < current_count; i++)
        contacts[i].displaySummary(i);
    std::cout << std::endl;
    std::cout << "Enter the index of the contact to display: ";
    std::string input;
    std::getline(std::cin, input);
    int idx = -1;
    if (input.size() == 1 && std::isdigit(input[0]))
        idx = input[0] - '0';
    if (idx >= 0 && idx < current_count)
        contacts[idx].displayDetails();
    else
        std::cout << "Invalid index.";
    std::cout << std::endl;
}
