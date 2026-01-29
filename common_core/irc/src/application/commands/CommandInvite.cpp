/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandInvite.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:21:29 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/02 23:22:37 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandInvite.hpp"

CommandInvite::CommandInvite(IUserRepositoryPort &userRepo, UseCases &useCases, IChannelRepositoryPort &channelRepo)
	: userRepo(userRepo), channelRepo(channelRepo), useCases(useCases) {}

CommandInvite::~CommandInvite() {}

void CommandInvite::execute(IRCMessage msg, unsigned long client_id)
{
	User &sender = this->userRepo.getOrCreate(client_id);
	User *dest = this->userRepo.getByNickName(msg.params[0]);
	Channel *channel = this->channelRepo.getChannel(msg.params[1]);

	if (!dest)
		throw NoSuchNickException(msg.params[0]);

	if (!channel)
		throw NoSuchChannelException(msg.params[1]);

	std::map<User *, bool> users = channel->getUsers();

	if (!channel->isInUsers(sender))
		throw NotOnChannelException(channel->getName());

	if (channel->getInviteOnly() && !channel->isOperator(sender))
		throw ChanOperatorNeededException(channel->getName());

	if (channel->isInUsers(*dest))
		throw StatusException(ERR_USERONCHANNEL, dest->getNickName() + " " + channel->getName() + " :is already on channel");
	if (channel->isInvited(dest->getNickName()))
		return this->useCases.informUser->execute(sender, "You have invited " + dest->getNickName() + " to join " + channel->getName());

	channel->addInvited(*dest);
	this->useCases.informUser->execute(*dest, sender.getNickName() + " INVITE " + dest->getNickName() + " :" + channel->getName());
	this->useCases.informUser->execute(sender, "You have invited " + dest->getNickName() + " to join " + channel->getName());
}
