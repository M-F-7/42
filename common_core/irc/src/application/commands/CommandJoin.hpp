/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandJoin.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:34:16 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 16:02:06 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IChannelRepository.hpp"
#include "UseCases.hpp"

class CommandJoin : public ICommand
{
private:
	UseCases &_usesCases;
	IUserRepositoryPort &_userRepo;
	IChannelRepositoryPort &_channelRepo;
	void _checkChannelPass(Channel &currChannel, IRCMessage &msg, size_t *i);

public:
	CommandJoin(IUserRepositoryPort &userRepo, IChannelRepositoryPort &channelRepo, UseCases &useCases);
	~CommandJoin();

	void execute(IRCMessage msg, unsigned long client_id);
};


//TODO

// If a JOIN is successful, the user receives a JOIN message as
//    confirmation and is then sent the channel's topic (using RPL_TOPIC) and
//    the list of users who are on the channel (using RPL_NAMREPLY), which
//    MUST include the user joining.
// 