/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:58:57 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/14 23:30:20 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "AMateria.hpp"
#include "ICharacter.hpp"

class Character : public ICharacter{
  
public:
    Character();
    Character(const std::string name);
    Character(const Character& other);
    Character& operator=(const Character& other);
    ~Character();
    
    std::string const & getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);

private:
    std::string _name;
    AMateria*   _inventory[4];

protected:

};