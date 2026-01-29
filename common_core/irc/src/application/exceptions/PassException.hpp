/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassException.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:14:58 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/12 09:56:36 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "StatusException.hpp"
#include <sstream>

class PassException : public StatusException
{
protected:
public:
	PassException(std::string pass, StatusCode status, std::string msg);
};

class PassNotMatch : public PassException
{
public:
	PassNotMatch();
};
