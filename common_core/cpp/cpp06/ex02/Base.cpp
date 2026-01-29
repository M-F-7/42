/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:28:35 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/19 15:30:42 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base::Base(){
    std::cout << "Base default constructor called"
                << std::endl;
}

Base::~Base(){
    std::cout << "Base destructor called"
                << std::endl;
}
    
Base * Base::generate(void){
    int random = 1 + (std::rand() % 3);
    if (random == 1)
        return new A();
    else if (random == 2)
        return new B();
    else if (random == 3)
        return new C();
    return NULL;
}

void Base::identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown type" << std::endl;
}

void Base::identify(Base& p) {
    try {
        A& a = dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        (void)a;
        return;
    }
    catch (...) {
        
    }
    
    try {
        B& b = dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        (void)b;
        return;
    }
    catch (...) {
    }
    
    try {
        C& c = dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        (void)c;
        return;
    }
    catch (...) {
        std::cout << "Unknown type" << std::endl;
    }
}