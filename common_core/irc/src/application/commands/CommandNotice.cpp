/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNotice.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:48:07 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 02:09:08 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandNotice.hpp"

CommandNotice::CommandNotice(IUserRepositoryPort &userRepo, UseCases &usesCase)
	: _userRepo(userRepo), _usesCases(usesCase) {};

CommandNotice::~CommandNotice() {};

void CommandNotice::execute(IRCMessage msg, unsigned long client_id)
{
	User &currUser = this->_userRepo.getOrCreate(client_id);

	this->_handleUsers(msg, currUser);
};

void CommandNotice::_handleUsers(IRCMessage msg, User &currUser)
{
	try
	{
		std::string message;
		User *destUser = this->_userRepo.getByNickName(msg.params[0]);
		if (!destUser)
			throw NoSuchNickException(msg.params[0]);
		for (size_t i = 1; i < msg.params.size(); i++)
		{
			message += msg.params[i];
			if (i + 1 < msg.params.size())
				message += " ";
		}
		this->_usesCases.informUser->execute(*destUser, currUser.getNickName() + " :" + message);
	}
	catch (StatusException &e)
	{
		this->_usesCases.informSenderError->execute(&currUser, e);
	}
}
