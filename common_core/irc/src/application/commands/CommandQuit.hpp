/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandQuit.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:50:05 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 16:33:16 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IPublisher.hpp"
#include "IChannelRepository.hpp"
#include "NetworkException.hpp"
#include "Client.hpp"
#include "User.hpp"
#include "ServerConfig.hpp"
#include <use_cases/InformChannel.hpp>
#include <use_cases/DisconnectUser.hpp>

class CommandQuit : public ICommand
{
public:
	CommandQuit(IUserRepositoryPort &userRepo, InformChannel &informChannel, IChannelRepositoryPort &channelRepo, DisconnectUser &disconnectUser);
	~CommandQuit();

	void execute(IRCMessage msg, unsigned long client_id);

private:
	IUserRepositoryPort &_userRepo;
	IChannelRepositoryPort &_channelRepo;
	InformChannel &_informChannel;
	DisconnectUser &_disconnectUser;
};
