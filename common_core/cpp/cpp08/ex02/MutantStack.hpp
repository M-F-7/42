/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:44:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/18 22:07:39 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <list>

template <typename T>
class MutantStack : public std::stack<T> {

public:
    MutantStack();
    MutantStack(const MutantStack<T>& other);
    MutantStack& operator=(const MutantStack<T>& other);
    ~MutantStack();

    typedef typename std::stack<T>::container_type::iterator iterator;

    iterator begin();
    iterator end();

    
};


#include "MutantStack.tpp"