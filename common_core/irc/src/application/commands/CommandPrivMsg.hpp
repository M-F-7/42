/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandPrivMsg.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:26:38 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 15:39:31 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IChannelRepository.hpp"
#include "IUserRepository.hpp"
#include "InformChannel.hpp"
#include "UseCases.hpp"

class CommandPrivMsg : public ICommand
{
private:
	IUserRepositoryPort &_userRepo;
	IChannelRepositoryPort &_channelRepo;
	UseCases &_usesCases;
	void _handleChannels(IRCMessage msg, User &currUser);
	void _handleUsers(IRCMessage msg, User &currUser);

public:
	CommandPrivMsg(IUserRepositoryPort &userRepo, UseCases &usesCases, IChannelRepositoryPort &channelRepo);

	~CommandPrivMsg();

	void execute(IRCMessage msg, unsigned long client_id);
};
