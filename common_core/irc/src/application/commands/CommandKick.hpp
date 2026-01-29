/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandKick.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:13:44 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 17:10:45 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IPublisher.hpp"
#include "IUserRepository.hpp"
#include "IChannelRepository.hpp"

class CommandKick : public ICommand
{
private:
	IChannelRepositoryPort &_channelRepo;
	IUserRepositoryPort &_userRepo;
	IPublisher &_publisher;

	void _handle_channel_kick(Channel &chan, User &user, IRCMessage &msg);
	void _shameOnYouBitch(Channel &chan, IRCMessage &msg, std::string user);

public:
	CommandKick(IChannelRepositoryPort &channelRepo, IUserRepositoryPort &userRepo, IPublisher &publisher);

	void execute(IRCMessage msg, unsigned long client_id);
};
