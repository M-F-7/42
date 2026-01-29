/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:23:47 by mfernand          #+#    #+#             */
/*   Updated: 2025/08/19 15:30:10 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma  once

#include <cstdlib>
#include <ctime>
#include <iostream>

class Base{

public:

    Base();
    virtual ~Base();
    Base * generate(void);
    void identify(Base* p);
    void identify(Base& p);
};
