/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:12 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/11 00:08:57 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(){

    Zombie foo("Foo");
    foo.announce();

    Zombie *bar = newZombie("bar");
    bar->announce();
    
    randomChump("Last boy");
    
    delete bar ;
    return (0);
}