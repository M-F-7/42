/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:43:36 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/21 19:36:03 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
    Span sp = Span(5);
    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    // try {
    //     sp.addNumber(5);
    // }
    // catch (std::exception &e){
    //     std::cout << "Exception caught: "
    //                 << e.what()
    //                 << std::endl;
    // }
    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;

    
    Span empty(0);

    try{
        std::cout << empty.shortestSpan() 
                    << std::endl;
    }
    catch (std::exception &e){
        std::cout << "Exception caught: "
                    << e.what()
                    << std::endl;
    }

    Span solo(1);
    solo.addNumber(5);
    try{
        std::cout << solo.shortestSpan()
                    << std::endl;
    }
    catch (std::exception &e){
        std::cout << "Exception caught: "
                    << e.what()
                    << std::endl;
    }

    try{
        std::cout << solo.longestSpan()
                    << std::endl;
    }
    catch (std::exception &e){
        std::cout << "Exception caught: "
                    << e.what()
                    << std::endl;
    }



    Span test(10);

    test.addNumber(584);
    test.addNumber(140); //shortest span
    test.addNumber(673);
    test.addNumber(987);//bigger
    test.addNumber(102);//smaller
    test.addNumber(869);
    test.addNumber(166);
    test.addNumber(145); //shortest span
    test.addNumber(254);
    test.addNumber(689);

    std::cout << test.shortestSpan()
                << std::endl;
    std::cout << test.longestSpan()
                << std::endl;

    Span big(50001);
    
    std::vector<int> v;
    int value = 1;
    for (int i = 0; i <= 50000; i++){
        if (i % 2)
            v.push_back(value * 2);
        else
            v.push_back(value / 2);
        value++;
    }
    big.addNumbers(v.begin(), v.end());

    std::cout << big.shortestSpan()
                << std::endl;
    std::cout << big.longestSpan()
                << std::endl;
    return 0;
}