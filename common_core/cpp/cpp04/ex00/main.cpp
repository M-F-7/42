/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:17:01 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/13 14:23:59 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"
#include "WrongDog.hpp"

int main(){
    
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound();
    j->makeSound();
    meta->makeSound();

    std::cout << std::endl
                << "Wrong Cat Part:"
                <<std::endl;
    const WrongAnimal *a = new WrongAnimal();
    const WrongAnimal *b = new WrongCat();
    std::cout << b->getType() << " " << std::endl;
    a->makeSound();
    b->makeSound();

    std::cout << std::endl
                << "Wrong Dog Part:"
                <<std::endl;
    const WrongAnimal *x = new WrongAnimal();
    const WrongAnimal *y = new WrongDog();
    std::cout << y->getType() << " " << std::endl;
    x->makeSound();
    y->makeSound();
    

    std::cout << std::endl;
    delete meta, delete i, delete j, delete a, delete b, delete x, delete y;
    return (0);
}
