/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 20:31:44 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie{

public:
    Zombie(std::string name);
    ~Zombie();
    
    void announce( void );
private:
    std::string name;
    
};

Zombie* newZombie( std::string name );
void randomChump( std::string name );

#endif 