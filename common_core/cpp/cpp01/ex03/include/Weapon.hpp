/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:10:13 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 21:40:59 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon{

public:
    Weapon();
    Weapon(const std::string& type); 
    ~Weapon();

    const  std::string& getType() const;
    void setType(const std::string& type);
private:

    std::string type;
};

#endif