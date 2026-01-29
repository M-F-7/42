/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:11:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 19:44:02 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

class Exceptions
{
public:
	class NotPermLimit : public std::exception
	{
		virtual const char *what() const throw();
	};

	class NotPermPass : public std::exception
	{
		virtual const char *what() const throw();
	};

	class NotPermTheme : public std::exception
	{
		virtual const char *what() const throw();
	};
};
