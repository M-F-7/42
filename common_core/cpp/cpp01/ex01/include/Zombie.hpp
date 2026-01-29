/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 20:53:58 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie{

public:
    Zombie();
    Zombie(std::string name);
    ~Zombie();
    
    void announce( void );
    void setName(std::string name);
private:
    std::string name;
    
};

Zombie* zombieHorde( int N, std::string name );

#endif 