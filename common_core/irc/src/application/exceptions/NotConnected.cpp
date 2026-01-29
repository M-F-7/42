/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NotConnected.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:51:35 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/30 14:54:56 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NotConnected.hpp"


NotConnected::NotConnected(CommandType cmd)
{
	std::string str = commandTypeToString(cmd);
	this->mgs = "451 * " + str + " :You have not registered" + "\r";
}

NotConnected::~NotConnected() throw() {};

const char *NotConnected::what() const throw()
{
	return (mgs.c_str());
}