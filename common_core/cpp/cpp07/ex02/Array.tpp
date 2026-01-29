/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 15:16:14 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/21 13:53:22 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

    
template <typename T> Array<T>::Array() {
    std::cout << "Array default constructor called"
                << std::endl;
    this->_tab = new T[0];
    this->_size = 0;    
}
    
    
template <typename T> Array<T>::Array(unsigned int n) {
    std::cout << "Array with param constrcutor called"
                << std::endl;
    this->_tab = new T[n];
    this->_size = n;
}
    
    
template <typename T> Array<T>::Array(const Array<T>& other) {
    std::cout << "Array copy constructor called"
                << std::endl;
    this->_tab = new T[other._size];
    for (unsigned int i = 0; i < other._size; i++)
        this->_tab[i] = other._tab[i];
    this->_size = other._size;
}
    
    
template <typename T> Array<T>& Array<T>::operator=(const Array<T>& other) {
    std::cout << "Array copy assignement operator called"
                << std::endl;
    
    if (this == &other)
        return *this;
    if (this->_tab)
        delete [] this->_tab;
    this->_tab = new T[other._size];
    for (unsigned int i = 0; i < other._size; i++)
        this->_tab[i] = other._tab[i];
    this->_size = other._size;
    return *this;
}
    
    
template <typename T>Array<T>::~Array() {
    std::cout << "Array destructor called"
                << std::endl;
    delete [] this->_tab;
}

template <typename T> int Array<T>::size() const{
    return _size;
}

template <typename T> const char* Array<T>::IdxTooHigh::what() const throw(){
    return "Idx > size";
}

template <typename T>  T& Array<T>::operator[](unsigned int idx){
    if (idx >= this->_size)
        throw IdxTooHigh();
    return this->_tab[idx];
}