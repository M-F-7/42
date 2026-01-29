/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:11:06 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/08 00:52:00 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanB{
    
public:
    HumanB();
    HumanB(const std::string& name);
    ~HumanB();    

    void attack();
    void setWeapon(Weapon& weapon);
private:

    Weapon* weapon;
    const std::string name;

};

#endif