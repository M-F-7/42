/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FakeParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moss <moss@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:31:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 11:53:49 by moss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IParser.hpp"

class FakeParser : public IParser
{
private:
	IRCMessage *_nextMsg;

public:
	FakeParser() : _nextMsg(NULL) {};
	~FakeParser() {};

	void next(IRCMessage &msg);
	IRCMessage parseMessage(const std::string &line);
	IRCMessage &getNextMessage() { return *_nextMsg; }
};
