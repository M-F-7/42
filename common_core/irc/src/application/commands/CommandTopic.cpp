/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandTopic.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:20:44 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 23:26:52 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandTopic.hpp"

CommandTopic::CommandTopic(IUserRepositoryPort &userRepo, UseCases &usesCases, IChannelRepositoryPort &channelRepo)
	: _userRepo(userRepo), _channelRepo(channelRepo), _usesCases(usesCases) {};

CommandTopic::~CommandTopic() {};

void CommandTopic::execute(IRCMessage msg, unsigned long client_id)
{
	Channel *channel = this->_channelRepo.getChannel(msg.params[0]);

	if (!channel)
		throw NoSuchChannelException(msg.params[0]);

	User &user = this->_userRepo.getOrCreate(client_id);

	if (!channel->isInUsers(user))
		throw NotOnChannelException(channel->getName());

	if (channel->getTopicLock())
		throw StatusException(ERR_NOCHANMODES, channel->getName() + " :Channel doesn't support modes");
	if (msg.params.size() == 1 && !msg.params[0].compare(channel->getName()))
		return this->_displayTopic(*channel);
	if (!channel->isOperator(user))
		throw ChanOperatorNeededException(channel->getName());
	channel->setTheme(msg.params[1]);
	this->_usesCases.informChannel->execute(*channel, &user, "332 " + user.getNickName() + " " + channel->getName() + " :" + channel->getTheme());
}

void CommandTopic::_displayTopic(Channel &channel)
{
	if (channel.getTheme().empty())
		throw StatusException(RPL_NOTOPIC, channel.getName() + " :No topic is set");
	throw StatusException(RPL_TOPIC, channel.getName() + " :" + channel.getTheme());
}
