/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 14:32:43 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/14 14:47:49 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>


template <typename T> void swap(T& a, T& b){
    T c;
    c = a;
    a = b;
    b = c;
}
template <typename T> T min(T a, T b){
    if (a < b)
        return a;
    return b;
}

template <typename T> T max(T a, T b){
    if (a > b)
        return a;
    return b;
}

