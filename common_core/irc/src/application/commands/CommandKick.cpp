/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandKick.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:16:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 18:12:59 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandKick.hpp"

CommandKick::CommandKick(IChannelRepositoryPort &channelRepo, IUserRepositoryPort &userRepo, IPublisher &publisher) : _channelRepo(channelRepo), _userRepo(userRepo), _publisher(publisher) {};

void CommandKick::execute(IRCMessage msg, unsigned long client_id)
{
	User &currentUser = this->_userRepo.getOrCreate(client_id);
	Response res(currentUser);
	Channel *channel;

	for (size_t i = 0; i < msg.params.size(); i++)
	{
		try
		{
			channel = this->_channelRepo.getChannel(msg.params[i]);
			if (!channel)
				throw NoSuchChannelException(msg.params[i]);
			this->_handle_channel_kick(*channel, currentUser, msg);
		}
		catch (StatusException &e)
		{
			res.setMsg(e.what());
			res.setStatusCode(e.getStatus());
			this->_publisher.publish(res);
		}
	}
};

void CommandKick::_handle_channel_kick(Channel &chan, User &user, IRCMessage &msg)
{
	Response res(user);

	if (!chan.isInUsers(user))
		throw NotOnChannelException(chan.getName());
	if (!chan.isOperator(user))
		throw ChanOperatorNeededException(chan.getName());
	for (size_t i = 0; i < msg.trailing.size(); i++)
	{
		try
		{
			if (!chan.isInUsers(msg.trailing[i]))
				throw UserNotInChannelException(msg.trailing[i], chan.getName());
			User *kicked = this->_userRepo.getByNickName(msg.trailing[i]);
			chan.addBanned(*kicked);
			this->_shameOnYouBitch(chan, msg, msg.trailing[i]);
		}
		catch (StatusException &e)
		{
			res.setMsg(e.what());
			res.setStatusCode(e.getStatus());
			this->_publisher.publish(res);
		}
	}
}
void CommandKick::_shameOnYouBitch(Channel &chan, IRCMessage &msg, std::string user)
{
	std::string message = "Command to kick " + user + " from " + chan.getName();
	if (!msg.reason.empty())
	{
		message += " using \"";
		message += msg.reason;
		message += "\" as the reason (comment).";
	}
	std::map<User *, bool> users = chan.getUsers();
	std::map<User *, bool>::iterator it = users.begin();
	std::map<User *, bool>::iterator ite = users.end();

	for (; it != ite; it++)
	{
		Response res(*it->first);
		res.setMsg(message);
		this->_publisher.publish(res);
	}
};
