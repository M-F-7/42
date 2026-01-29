/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:34:20 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/07 20:57:09 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

Zombie* zombieHorde( int N, std::string name ){
    
    if (N <= 0)
        return NULL;
    Zombie *zombieHorde = new Zombie[N];
    for (int i = 0; i < N; ++i) {
        zombieHorde[i].setName(name);
    }
    return (zombieHorde);
}
