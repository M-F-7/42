/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:54:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/11 18:40:56 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"


Harl::Harl(){

}

Harl::~Harl(){
    
}



void Harl::debug( void ){  
    std::cout << "[DEBUG]" 
                << std::endl 
                << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I really do!" 
                << std::endl
                << std::endl;
}

void Harl::info( void ){
    std::cout << "[INFO]" 
                << std::endl 
                << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! If you did, I wouldn't be asking for more!" 
                << std::endl
                << std::endl;
}
    
void Harl::warning( void ){
    std::cout << "[WARNING]" 
                << std::endl 
                << "I think I deserve to have some extra bacon for free. I’ve been coming for years, whereas you started working here just last month." 
                << std::endl
                << std::endl;
}
    
void Harl::error( void ){
    std::cout << "[ERROR]" 
                << std::endl
                << "This is unacceptable! I want to speak to the manager now."
                << std::endl;
}

void Harl::complain( std::string level ){

    std::string foo[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    void (Harl::*bar[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};

    int i = -1;
    while(++i < 4)
    {
        if (foo[i] == level)
        {
            switch (i){
        
                case 0:
                    while(i < 4)
                        (this->*bar[i++])();
                    break;
            
                case 1:
                    while(i < 4)
                        (this->*bar[i++])();
                    break;
            
                case 2:
                    while(i < 4)
                        (this->*bar[i++])();
                    break;
            
                case 3:
                    while(i < 4)
                        (this->*bar[i++])();
                    break;
                
                default:
                    break;
            }
        }
    }
    if (i == 4)
        std::cout << "[ Probably complaining about insignificant problems ]";
}
