/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 20:56:27 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/18 22:07:33 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::begin(){
    return this->c.begin();
}

template <typename T>
typename MutantStack<T>::iterator MutantStack<T>::end(){ 
    return this->c.end(); 
}

template <typename T>
MutantStack<T>::MutantStack(){
    std::cout << "MutantStack default constructor called"
                << std::endl;
}
    

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T>& other) : std::stack<T>(other){
    std::cout << "MutantStack copy constructor called"
                << std::endl;
    (void)other;
}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack<T>& other){
    std::cout << "MutantStack copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    std::stack<T>::operator=(other);
    return *this;
}

template <typename T>
MutantStack<T>::~MutantStack(){
    std::cout << "MutantStack destructor called"
                <<std::endl;
}