/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:17:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 12:58:06 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"
#include "WrongDog.hpp"
#include "Brain.hpp"

int main(){
    
    const Animal* tab[100];

    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 0)
            tab[i] = new Cat();
        else
            tab[i] = new Dog();
    }
    for (int i = 0; i < 100; i++)
        delete tab[i]; //must destroy the derived object, then the member (brain), then the parent
    
    std::cout << std::endl;
    Cat original;
    original.getBrain()->setIdea(0, "Je suis l'original");

    Cat copy = original;
    copy.getBrain()->setIdea(0, "Je suis la copie"); //must modify only copy and not the original for deep copy

    std::cout << "Original: " << original.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copy: " << copy.getBrain()->getIdea(0) << std::endl;



    
    std::cout << std::endl;
    Dog original2;
    original2.getBrain()->setIdea(0, "Je suis l'original2");

    Dog copy2 = original2;
    copy2.getBrain()->setIdea(0, "Je suis la copie2"); //must modify only copy and not the original for deep copy

    std::cout << "Original: " << original2.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copy: " << copy2.getBrain()->getIdea(0) << std::endl;

    

    
    std::cout << std::endl;
    return (0);
}
