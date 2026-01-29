/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongDog.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:02:17 by mfernand          #+#    #+#             */
/*   Updated: 2025/07/14 22:10:18 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "WrongAnimal.hpp"

class WrongDog : public WrongAnimal{
  
public:
    WrongDog();
    WrongDog(const WrongDog& other);
    WrongDog& operator=(const WrongDog& other);
    ~WrongDog();

    void makeSound() const;
    void setType(const std::string& type);
    std::string getType() const;
private:

protected:
};
