/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:33:39 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 00:14:16 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "AMateria.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "MateriaSource.hpp"


int main(){
    
    std::cout << "42 Test :"
                << std::endl;
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());
    ICharacter* me = new Character("me");
    AMateria* tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    ICharacter* bob = new Character("bob");
    me->use(0, *bob);
    me->use(1, *bob);

    std::cout << std::endl
                << "my tests :"
                << std::endl;


    ICharacter* foo = new Character("foo");
    foo->use(0, *foo); //nothing happened
    foo->use(3, *foo); //nothing happened
    
    AMateria* m1 = src->createMateria("ice");
    AMateria* m2 = src->createMateria("cure");
    AMateria* m3 = src->createMateria("ice");
    AMateria* m4 = src->createMateria("cure");
    AMateria* m5 = src->createMateria("ice");
    foo->equip(m1);
    foo->equip(m2);
    foo->equip(m3);
    foo->equip(m4);
    foo->equip(m5); //nothing happened
    foo->use(0, *foo); // * shoots an ice bolt at foo *
    foo->use(1, *foo); // * heals foo's wounds *
    foo->use(2, *foo); // * shoots an ice bolt at foo *
    foo->use(3, *foo); // * heals foo's wounds *
    
    foo->unequip(1); //just unequip, not delete
    delete m2;       // delete here
    foo->use(1, *foo); // empty slot so nothing happened

    Character bob2("bob2");
    bob2 = *(static_cast<Character*>(foo));
    bob2.use(0, bob2); // * shoots an ice bolt at bob2 * --> copy of foo[0](ice)

    delete m5;
    delete foo;

    AMateria* unknown = src->createMateria("fire"); // createMateria must return NULL so print the error
    if (!unknown)
        std::cout << "Unknown materia creation returned error as expected." 
                    << std::endl;

    delete unknown;
    delete bob;
    delete me;
    delete src;
    
    return 0;
}