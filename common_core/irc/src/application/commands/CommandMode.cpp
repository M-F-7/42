/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMode.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:06:22 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 01:55:14 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandMode.hpp"

CommandMode::CommandMode(IUserRepositoryPort &userRepo, UseCases &useCases, IChannelRepositoryPort &channelRepo)
	: userRepo(userRepo), channelRepo(channelRepo), useCases(useCases) {}

CommandMode::~CommandMode() {}

void CommandMode::execute(IRCMessage msg, unsigned long client_id)
{
	User &user = this->userRepo.getOrCreate(client_id);
	Channel *channel = this->channelRepo.getChannel(msg.params[0]);

	if (!channel)
		throw NoSuchChannelException(msg.params[0]);
	if (!channel->isInUsers(user))
		throw NotOnChannelException(channel->getName());
	if (msg.params.size() == 1)
		return this->_displayModes(*channel, user);
	if (!channel->isOperator(user))
		throw ChanOperatorNeededException(channel->getName());
	this->_handleModifications(*channel, msg);
}

void CommandMode::_handleModifications(Channel &chan, IRCMessage &msg)
{
	bool activateMode = false;

	std::string modes = msg.params[1];
	size_t modeParamIndex = 0;

	if (modes[0] == '+')
		activateMode = true;
	else
		activateMode = false;
	for (size_t i = 1; i < modes.size(); i++)
	{
		if (modes[i] == 'i')
			chan.setInviteOnly(activateMode);
		else if (modes[i] == 't')
			chan.setTopicLock(activateMode);
		else if (modes[i] == 'k' && activateMode)
			chan.setPass(msg.params[1 + ++modeParamIndex]);
		else if (modes[i] == 'k')
			chan.setPass("");
		else if (modes[i] == 'l' && activateMode)
			_handleLimitModification(chan, msg.params[1 + ++modeParamIndex]);
		else if (modes[i] == 'l')
			chan.setLimit(0);
		else if (modes[i] == 'o' && activateMode)
			chan.giveOperator(msg.params[1 + ++modeParamIndex]);
		else if (modes[i] == 'o')
			chan.removeOperator(msg.params[1 + ++modeParamIndex]);
		else if (modes[i] == '-')
			activateMode = false;
		else
			throw StatusException(ERR_NOCHANMODES, chan.getName() + " :Channel doesn't support modes");
	}
}

void CommandMode::_handleLimitModification(Channel &chan, std::string strLimit)
{
	std::istringstream iss(strLimit);
	unsigned long limit = 0;

	iss >> limit;
	chan.setLimit(limit);
}

void CommandMode::_informChanAboutModifications(Channel &chan, User &user, IRCMessage &msg)
{
	std::string modeChange = chan.getName() + " " + msg.params[0];
	for (size_t i = 2; i < msg.params.size(); i++)
		modeChange += " " + msg.params[i];
	this->useCases.informChannel->execute(chan, &user, modeChange);
}

void CommandMode::_displayModes(Channel &chan, User &user)
{
	Response res(user);
	std::string msg = chan.getName() + " ";
	std::string modes;
	std::string params;

	res.setStatusCode(RPL_CHANNELMODEIS);

	if (chan.getInviteOnly())
		modes += "i";
	if (chan.getTopicLock())
		modes += "t";
	if (chan.getPassUp())
	{
		modes += "k";
		params += chan.getPass();
	}
	if (chan.getIsLimited())
	{
		modes += "l";
		params += chan.getLimit();
	}
	if (!modes.empty())
		msg += "+" + modes;

	res.setMsg(msg);
	this->useCases.sendReponse->execute(res);
}
