/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:34:21 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/14 23:33:30 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class ICharacter;
class IMateriaSource;

class AMateria
{
    protected:
    
    std::string type;
    
    public:

    AMateria(std::string const & type);
    virtual ~AMateria();
    AMateria(const AMateria& other);
    AMateria& operator=(const AMateria& other);
    
    std::string const & getType() const; //Returns the materia type
    
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};

#