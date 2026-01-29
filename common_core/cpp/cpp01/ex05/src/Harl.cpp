/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/08 13:53:29 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"


Harl::Harl(){

}

Harl::~Harl(){
    
}



void Harl::debug( void ){  
    std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" 
                << std::endl;
}

void Harl::info( void ){
    std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" 
                << std::endl;
}
    
void Harl::warning( void ){
    std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." 
                << std::endl;
}
    
void Harl::error( void ){
    std::cout << "This is unacceptable! I want to speak to the manager now."
                << std::endl;
}

void Harl::complain( std::string level ){

    std::string foo[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    void (Harl::*bar[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

    for (int i = 0; i < 4; i++)
    {
        if (level == foo[i])
        {
            (this->*bar[i])();
            break;
        }
    }
}