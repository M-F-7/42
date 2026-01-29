/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPrivMsg.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:46:19 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 18:54:39 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandPrivMsg.hpp"

CommandPrivMsg::CommandPrivMsg(IUserRepositoryPort &userRepo, UseCases &usesCases, IChannelRepositoryPort &channelRepo) : _userRepo(userRepo), _channelRepo(channelRepo), _usesCases(usesCases) {};

CommandPrivMsg::~CommandPrivMsg() {};

void CommandPrivMsg::execute(IRCMessage msg, unsigned long client_id)
{
	User &currUser = this->_userRepo.getOrCreate(client_id);

	this->_handleChannels(msg, currUser);
	this->_handleUsers(msg, currUser);
};

void CommandPrivMsg::_handleChannels(IRCMessage msg, User &currUser)
{
	for (size_t i = 0; i < msg.params.size(); i++)
	{
		try
		{
			Channel *currChannel = this->_channelRepo.getChannel(msg.params[i]);
			if (!currChannel)
				throw NoSuchChannelException(msg.params[i]);
			if (currChannel->isBanned(currUser.getNickName()))
				throw CannotSendToChanException(currChannel->getName());
			if (!currChannel->isInUsers(currUser))
				throw CannotSendToChanException(currChannel->getName());
			this->_usesCases.informChannel->execute(*currChannel, &currUser, currUser.getNickName() + ": " + msg.reason);
			this->_usesCases.informUser->execute(currUser, "Message sent to channel " + currChannel->getName());
		}
		catch (StatusException &e)
		{
			this->_usesCases.informSenderError->execute(&currUser, e);
		}
	}
}

void CommandPrivMsg::_handleUsers(IRCMessage msg, User &currUser)
{
	for (size_t i = 0; i < msg.trailing.size(); i++)
	{
		try
		{
			User *destUser = this->_userRepo.getByNickName(msg.trailing[i]);
			if (!destUser)
				throw NoSuchNickException(msg.trailing[i]);
			this->_usesCases.informUser->execute(*destUser, currUser.getNickName() + " :" + msg.reason);
			this->_usesCases.informUser->execute(currUser, "Message sent to user " + destUser->getNickName());
		}
		catch (StatusException &e)
		{
			this->_usesCases.informSenderError->execute(&currUser, e);
		}
	}
}
