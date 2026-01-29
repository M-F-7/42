/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:48:04 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/21 19:33:08 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(){
    std::cout << "Span default construtor called"
                << std::endl;
    this->_tab = new int[0];
    this->_size = 0;
    this->_idx = 0;
}
    
Span::Span(unsigned int N){
    std::cout << "Span param constructor called"
                << std::endl;
    this->_tab = new int[N];
    this->_size = N;
    this->_idx = 0;
}
    
Span::Span(const Span& other){
    std::cout << "Span copy constructor called"
                << std::endl;
    this->_tab = new int[other._size];
    for (int i = 0; i < other._size; i++)
        this->_tab[i] = other._tab[i];
    this->_size = other._size;  
    this->_idx = 0;
    
}
    
Span& Span::operator=(Span& other){
    std::cout << "Span copy assignement operator called"
                << std::endl;
    if (this == &other)
        return *this;
    if (this->_tab)
        delete [] this->_tab;
    this->_tab = new int[other._size];
    for (int i = 0; i < other._size; i++)
        this->_tab[i] = other._tab[i];
    this->_size = other._size;  
    this->_idx = 0;
    return *this;
}
    
Span::~Span(){
    std::cout << "Span destructor called"
                << std::endl;
    delete [] this->_tab;
}

    
void Span::addNumber(int nb){
    if (this->_idx >= this->_size)
        throw NoMoreSpaceIn();
    this->_tab[this->_idx] = nb;
    this->_idx++;
}
    
int Span::shortestSpan(){
    if (this->_size <= 1)
        throw InvalidSpan();

    std::vector<int> tmp(this->_tab, this->_tab + this->_idx);
    std::sort(tmp.begin(), tmp.end());

    int res = tmp[1] - tmp[0];
    for (int i = 2; i < this->_size; i++){
        int diff = tmp[i] - tmp[i - 1];
        if (diff < res)
            res = diff;
    }
    return res;
}
    
int Span::longestSpan(){
    if (this->_size <= 1)
        throw InvalidSpan();

    int res = 0;
    int max = this->_tab[0];
    int min = this->_tab[0];

    for (int i = 0; i < this->_size; i++){
        if (this->_tab[i] > max)
            max = this->_tab[i];
        if (this->_tab[i] < min)
            min = this->_tab[i];
    }
    res = max - min;
    if (res < 0)
        res *= -1;
    return res;
}

const char* Span::NoMoreSpaceIn::what() const throw() {
	return "No more space in Span";
}

           
const char* Span::InvalidSpan::what() const throw(){
    return "The Span is empty or there is only one value";
}

void Span::addNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    for (std::vector<int>::iterator it = begin; it != end; ++it) {
        if (this->_idx >= this->_size)
            throw NoMoreSpaceIn();
        this->_tab[this->_idx] = *it;
        this->_idx++;
    }
}