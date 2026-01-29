/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:47:42 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 10:49:39 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include "../include/Contact.hpp"

class PhoneBook{

public :
    PhoneBook();
    ~PhoneBook();
    void addContact();
    void searchContact();
private :
    Contact contacts[8];
    int     nb_contacts;
    int current_count;
        
};

#endif