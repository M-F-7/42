/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPart.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:52:27 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/13 20:23:09 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IPublisher.hpp"
#include "Channel.hpp"
#include "IChannelRepository.hpp"

class CommandPart : public ICommand
{
private:
	IUserRepositoryPort &_userRepo;
	IPublisher &_publisher;
	IChannelRepositoryPort &_channelRepo;

public:
	CommandPart(IUserRepositoryPort &userRepo, IPublisher &publisher, IChannelRepositoryPort &channelRepo);
	~CommandPart();

	void execute(IRCMessage msg, unsigned long client_id);
};
