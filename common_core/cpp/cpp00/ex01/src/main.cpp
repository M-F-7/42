/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:48:55 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 02:55:24 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp"
#include "../include/Contact.hpp"

int main()
{
    std::string input;
    PhoneBook curr;
    while(true)
    {
        std::cout << "You can add a new contact(ADD), search one(SEARCH), or leave the program(EXIT)" << std::endl;
        std::cout << "> ";
        if (!std::getline(std::cin, input)) 
        {
            std::cout << "\nInput aborted." << std::endl;
            return (1);
        }
        if (input == "ADD")
            curr.addContact();
        else if (input == "SEARCH")
            curr.searchContact();
        else if (input == "EXIT")
            break;
        else
            std::cout << "You must enter a valid command" << std::endl;
    }
    return (0);
}
