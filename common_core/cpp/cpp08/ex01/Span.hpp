/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:44:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/21 19:33:45 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>
#include <algorithm>

class Span{

public:
    Span();
    Span(unsigned int N);
    Span(const Span& other);
    Span& operator=(Span& other);
    ~Span();

    void addNumber(int nb);
    int shortestSpan();
    int longestSpan();    

    void addNumbers(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    class NoMoreSpaceIn : public std::exception{
        public:
            const char* what() const throw();
    };
    class InvalidSpan : public std::exception{
        public:
            const char* what() const throw();
    };
private:
        int *_tab;
        int _size;
        int _idx;
};
