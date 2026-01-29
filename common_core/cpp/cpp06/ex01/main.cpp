/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:24:06 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/19 15:05:02 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main() {
    Data data;
    data.nb = 42;
    data.word = "WAIWAI";

    uintptr_t raw = Serializer::serialize(&data);

    Data* ptr = Serializer::deserialize(raw);

    std::cout << "\nOriigiinal address : " 
                << &data 
                << std::endl;
                
    std::cout << "Address post deserialization : " 
                << ptr 
                << std::endl;
                
    std::cout << "\nAddesses match: ";
                
    if (&data == ptr)
        std::cout << "Yes";
    else
        std::cout << "No";
    std::cout << "\n\n\n" << std::endl;


    
    std::cout << "Value nb data: " << data.nb << std::endl;
    std::cout << "Value nb ptr: " << ptr->nb << std::endl;

    std::cout << "\nValue match: ";
                
    if (data.nb == ptr->nb)
        std::cout << "Yes";
    else
        std::cout << "No";
    std::cout << "\n\n\n" << std::endl;


    
    std::cout << "Content word data: " << data.word << std::endl;
    std::cout << "Content word ptr: " << ptr->word << std::endl;

    std::cout << "\nWord match: ";
                
    if (data.word == ptr->word)
        std::cout << "Yes";
    else
        std::cout << "No";
    std::cout << "\n\n\n" << std::endl;

    return 0;
}
