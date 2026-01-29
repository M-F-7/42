/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:19:32 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/15 00:10:51 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"


MateriaSource::MateriaSource() {
    for (int i = 0; i < 4; i++)
        _materias[i] = NULL;
    std::cout << "MateriaSource default constructor called"
                << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource& other) {
    std::cout << "MateriaSource copy constructor called"
                << std::endl;
    for (int i = 0; i < 4; i++) {
        if (other._materias[i])
            _materias[i] = other._materias[i]->clone();
        else
            _materias[i] = NULL;
    }
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other){
    std::cout << "MateriaSource copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    for (int i = 0; i < 4; i++) {
        if (_materias[i])
            delete _materias[i];
        if (other._materias[i])
            _materias[i] = other._materias[i]->clone();
        else
            _materias[i] = NULL;
    }
    return *this;
}

MateriaSource::~MateriaSource(){
    for (int i = 0; i < 4; i++)
        if (_materias[i])
            delete _materias[i];
            
    std::cout << "MateriaSource destructor called"
                << std::endl;
}


void MateriaSource::learnMateria(AMateria* m){
    if (!m)
        return;
    for (int i = 0; i < 4; i++) {
        if (!_materias[i]) {
            _materias[i] = m;
            return;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const & type){
    for (int i = 0; i < 4; i++)
        if (_materias[i] && _materias[i]->getType() == type)
            return _materias[i]->clone();
    return NULL;
         
}