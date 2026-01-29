/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:11:05 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/08 00:50:14 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <iostream>
#include "Weapon.hpp"

class HumanA{
    
public:
    HumanA(const std::string& name, Weapon& weapon);
    ~HumanA();    

    void attack();
private:
    Weapon& weapon;
    const std::string name;

};

#endif