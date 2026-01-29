/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 14:43:36 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/21 19:39:23 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

int main()
{
    MutantStack<int> mstack;
    mstack.push(5);
    mstack.push(17);
    mstack.pop();
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;   
    }
    std::stack<int> s(mstack);


    std::cout << "\n\n\nLST PART: \n\n"
                << std::endl;
    
    std::list<int> mlst;
    mlst.push_back(5);
    mlst.push_back(17);
    mlst.pop_back();
    mlst.push_back(3);
    mlst.push_back(5);
    mlst.push_back(737);
    mlst.push_back(0);
    std::list<int>::iterator itt = mlst.begin();
    std::list<int>::iterator itee = mlst.end();
    ++itt;
    --itt;
    while (itt != itee)
    {
        std::cout << *itt << std::endl;
        ++itt;   
    }
    return 0;
}    