/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 20:33:09 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 10:33:58 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PhoneBook.hpp"
#include "../include/Contact.hpp"

Contact::Contact(): save(false){
}

Contact::~Contact(){
}

static std::string truncate(const std::string str){
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void Contact::fillContact(){

    int space_count = 0;
    size_t i = -1;
    bool valid = true;
    std::cout << std::endl;
    std::cout << "Enter a name : ";
    if (!std::getline(std::cin, name)) 
    {
        std::cout << "\nInput aborted." << std::endl;
        return;
    }
    while (!name.empty() && ++i < name.size())
    {
        space_count = 0;
        while (!name.empty() && std::isspace(name[0]))
            name.erase(0, 1);
        while (!name.empty() && std::isspace(name[name.size() - 1]))
            name.erase(name.size() - 1);
        if (name.empty())
            break;
        for (size_t j = 0; j < name.size(); ++j)
            if (std::isspace(name[j]) || name[j] == '-')
                space_count++;
        if (space_count > 2) 
        {
            std::cout << "Maximum 3 words (2 spaces) allowed for the name." << std::endl;
            std::cout << "Enter a valid name : ";
            if (!std::getline(std::cin, name)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
            continue;
        }
        else if (std::isspace(name[i]) && !std::isspace(name[i + 1]))
            continue;
        else if (name[i] == '-' && i != 0 && std::isalpha(name[i + 1]) && !std::isspace(name[i - 1]))
            continue;
        else if (!std::isalpha(name[i])  || !name[0])
        {
            std::cout << "Enter a valid name : ";
            if (!std::getline(std::cin, name)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
        }
    }
    std::cout << "Enter a last name : ";
    if (!std::getline(std::cin, last_name)) 
    {
        std::cout << "\nInput aborted." << std::endl;
        return;
    }
    i = -1;
    while (!last_name.empty() && ++i < last_name.size())
    {
        space_count = 0;
        while (!last_name.empty() && std::isspace(last_name[0]))
            last_name.erase(0, 1);
        while (!last_name.empty() && std::isspace(last_name[last_name.size() - 1]))
            last_name.erase(last_name.size() - 1);
        if (last_name.empty())
            break;
        for (size_t j = 0; j < last_name.size(); ++j)
            if (std::isspace(last_name[j]) || last_name[j] == '-')
                space_count++;
        if (space_count > 2)
        {
            std::cout << "Maximum 3 words (2 spaces) allowed for the last name." << std::endl;
            std::cout << "Enter a valid last name : ";
            if (!std::getline(std::cin, last_name)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
            continue;
        }
        else if (std::isspace(last_name[i]) && !std::isspace(last_name[i + 1]))
            continue;
        else if (last_name[i] == '-' && i != 0 && std::isalpha(last_name[i + 1]) && !std::isspace(last_name[i - 1]))
            continue;
        else if (!std::isalpha(last_name[i])  || !last_name[0])
        {
            std::cout << "Enter a valid last name : ";
            if (!std::getline(std::cin, last_name)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
        }
    }
    std::cout << "Enter a nickname : ";
    if (!std::getline(std::cin, nickname)) 
    {
        std::cout << "\nInput aborted." << std::endl;
        return;
    }
    i = -1;
    while (!nickname.empty() && ++i < nickname.size())
    {
        valid = true;
        if (nickname[0] == '"')
        {
            while(std::isspace(nickname[++i]) || nickname[i] == '"')
            {
                if (i == nickname.size() - 1)
                {
                    std::cout << "Enter a valid nickname : ";
                    if (!std::getline(std::cin, nickname)) 
                    {
                        std::cout << "\nInput aborted." << std::endl;
                        return;
                    }
                    i = -1;
                    valid = false;
                    break;
                }
            }
            if (!valid)
                continue;
        }
        while (!nickname.empty() && std::isspace(nickname[0]))
            nickname.erase(0, 1);
        while (!nickname.empty() && std::isspace(nickname[nickname.size() - 1]))
            nickname.erase(nickname.size() - 1);
        if (nickname.empty())
            break;
        if (nickname[0] == '"' && nickname[1] == '"')
        {
            std::cout << "Enter a valid nickname : ";
            if (!std::getline(std::cin, nickname)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
            continue;
        }
        else if (!nickname[0])
        {
            std::cout << "Enter a valid nickname : ";
            if (!std::getline(std::cin, nickname)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
        }
    }
    std::cout << "Enter a phone number 📞 : ";
    if (!std::getline(std::cin, phone_number)) 
    {
        std::cout << "\nInput aborted." << std::endl;
        return;
    }
    i = -1;
    while (!phone_number.empty() && ++i < phone_number.size())
    {
        valid = true;
        while (!phone_number.empty() && std::isspace(phone_number[0]))
            phone_number.erase(0, 1);
        while (!phone_number.empty() && std::isspace(phone_number[phone_number.size() - 1]))
            phone_number.erase(phone_number.size() - 1);
        if (phone_number.empty())
            break;
        if (phone_number.size() != 10)
            valid = false;
        for (size_t k = 0; k < phone_number.size(); ++k)
            if (!std::isdigit(phone_number[k]))
                valid = false;
        if (!valid)
        {
            std::cout << "Enter a valid phone number 📞 (10 digits): ";
            if (!std::getline(std::cin, phone_number)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
            continue;
        }
        else if (!std::isdigit(phone_number[i])  || !phone_number[0])
        {
            std::cout << "Enter a valid phone number 📞 : ";
            if (!std::getline(std::cin, phone_number)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
        }
    }
    std::cout << "Enter a secret 🙊: ";
    if (!std::getline(std::cin, secret)) 
    {
        std::cout << "\nInput aborted." << std::endl;
        return;
    }
    i = -1;
    while (!secret.empty() && ++i < secret.size())
    {
        valid = true;
        if (secret[0] == '"')
        {
            while(std::isspace(secret[++i]) || secret[i] == '"')
            {
                if (i == secret.size() - 1)
                {
                    std::cout << "Enter a valid secret 🙊 : ";
                    if (!std::getline(std::cin, secret)) 
                    {
                        std::cout << "\nInput aborted." << std::endl;
                        return;
                    }
                    i = -1;
                    valid = false;
                    break;
                }
            }
            if (!valid)
                continue;
        }
        while (!secret.empty() && std::isspace(secret[0]))
            secret.erase(0, 1);
        while (!secret.empty() && std::isspace(secret[secret.size() - 1]))
            secret.erase(secret.size() - 1);
        if (secret.empty())
            break;
        if (secret[0] == '"' && secret[1] == '"')
        {
            std::cout << "Enter a valid secret 🙊 : ";
            if (!std::getline(std::cin, secret)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
            continue;
        }
        else if (!secret[0])
        {
            std::cout << "Enter a valid secret 🙊 : ";
            if (!std::getline(std::cin, secret)) 
            {
                std::cout << "\nInput aborted." << std::endl;
                return;
            }
            i = -1;
        }
    }
    if (!name.empty() && !last_name.empty() && !nickname.empty() && !phone_number.empty() && !secret.empty())
        save = true;
    std::cout << std::endl;
}

void Contact::displaySummary(int index) {
    if (save)
    {
        std::cout << "|" << std::setw(10) << index
              << "|" << std::setw(10) << truncate(name)
              << "|" << std::setw(10) << truncate(last_name)
              << "|" << std::setw(10) << truncate(nickname)
              << "|" << std::endl;
    }
}

void Contact::displayDetails() {
    if (save) 
    {
        std::cout << "First name: " << name << std::endl;
        std::cout << "Last name: " << last_name << std::endl;
        std::cout << "Nickname: " << nickname << std::endl;
        std::cout << "Phone number: " << phone_number << std::endl;
        std::cout << "Secret: " << secret << std::endl;
    }
}

