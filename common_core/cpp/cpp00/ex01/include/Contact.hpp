/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 18:47:37 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 12:19:33 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <iomanip>

class Contact{

public :
    Contact();
    ~Contact();  
    bool isSaved() const { return save; }
    void    fillContact();
    void    displaySummary(int index);
    void    displayDetails();
private :
    std::string    name;
    std::string    last_name;
    std::string    nickname;
    std::string    phone_number;
    std::string    secret;
    bool           save;
};
#endif