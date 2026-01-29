/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPart.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:53:45 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 19:18:31 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandPart.hpp"

CommandPart::CommandPart(IUserRepositoryPort &userRepo, IPublisher &publisher, IChannelRepositoryPort &channelRepo) : _userRepo(userRepo), _publisher(publisher), _channelRepo(channelRepo) {};
CommandPart::~CommandPart() {};

void CommandPart::execute(IRCMessage msg, unsigned long client_id)
{
	User &user = this->_userRepo.getOrCreate(client_id);
	Response res(user);
	Channel *channel;

	for (size_t i = 0; i < msg.params.size(); i++)
	{
		try
		{
			channel = this->_channelRepo.getChannel(msg.params[i]);
			if (!channel)
				throw NoSuchChannelException(msg.params[i]);
			if (!channel->isInUsers(user))
				throw NotOnChannelException(msg.params[i]);
			channel->deleteUser(user);
			if (!msg.trailing.size())
				res.setMsg("Command to leave channel " + channel->getName());
			else
				res.setMsg("User " + user.getNickName() + " leaving channel \"" + channel->getName() + "\" with the message \"" + msg.trailing[0] + "\"");
			this->_publisher.publish(res);
		}
		catch (const StatusException &e)
		{
			res.setMsg(e.what());
			res.setStatusCode(e.getStatus());
			this->_publisher.publish(res);
		}
	}
}
