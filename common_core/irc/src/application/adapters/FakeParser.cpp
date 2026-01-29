/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FakeParser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:36:02 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 15:14:15 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FakeParser.hpp"

void FakeParser::next(IRCMessage &msg)
{
	this->_nextMsg = &msg;
}

IRCMessage& FakeParser::parseMessage(const std::string &)
{
	if (this->_nextMsg)
	{
		IRCMessage *msg = (this->_nextMsg);
		this->_nextMsg = NULL;
		return *msg;
	}
	throw std::runtime_error("No next message set in FakeParser");
}
