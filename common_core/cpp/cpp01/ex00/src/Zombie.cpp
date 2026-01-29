/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:51 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 20:31:41 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name): name(name){
    
}

Zombie::~Zombie(){
    std::cout << name
                << ": has been destroyed" 
                << std::endl;
}

void    Zombie::announce(){
    
    std::cout << name 
                << ": BraiiiiiiinnnzzzZ..." 
                << std::endl;
}