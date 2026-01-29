/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:43:36 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/15 20:24:09 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Easyfind.hpp"
#include <vector>

int main (){
    
    int res = 0;
    std::vector<int> v;
    for (int i = 0; i < 5; i++)
        v.push_back(i++);
    try{
        res = easyfind(v, 4);
        std::cout << res 
                    << std::endl;
        std::vector<int> v1;
        res = easyfind(v1, 4);
    }
    catch (std::exception& e) {
        std::cout << "Exception caught: "
                    << e.what() 
                    << std::endl;
    }

    try{
        res = easyfind(v, 89);
    }
    catch (std::exception& e){
        std::cout << "Exception caught: "
                    << e.what() 
                    << std::endl;
    }

    std::vector<char> v2;
    try{
        for (int i = 0; i < 5; i++)
            v2.push_back('a' + i);
        res = easyfind(v2, 'e');
        std::cout << static_cast<char>(res) 
                    << std::endl;
    }
    catch (std::exception& e){
        std::cout << "Exception caught: "
                    << e.what() 
                    << std::endl;
    }
}