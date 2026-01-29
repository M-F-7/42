/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:32:43 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/21 10:37:40 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>

template <typename T> void f(T& elt){
    elt++;
}

template <typename T> void iter(T *a, size_t size, void f(T& elt)){
    for (size_t i = 0; i < size; i++)
        f(a[i]);
}