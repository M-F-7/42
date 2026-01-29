/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:32:43 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/14 22:27:57 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>

template <class T> class Array{

public:
    Array();
    Array(unsigned int n);
    Array(const Array& other);
    Array& operator=(const Array& other);
    T& operator[](unsigned int idx);
    ~Array();

    int size() const;

    class IdxTooHigh: public std::exception{
        public:
            const char* what() const throw();     
    };
private:
    T *_tab;
    unsigned int _size;
};

#include "Array.tpp"