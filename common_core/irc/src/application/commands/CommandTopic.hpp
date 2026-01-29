/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandTopic.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 18:20:49 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/17 11:09:32 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IChannelRepository.hpp"
#include "UseCases.hpp"

class CommandTopic : public ICommand
{

private:
	IUserRepositoryPort &_userRepo;
	IChannelRepositoryPort &_channelRepo;
	UseCases &_usesCases;

	void _displayTopic(Channel &channel);

public:
	CommandTopic(IUserRepositoryPort &userRepo, UseCases &usesCases, IChannelRepositoryPort &channelRepo);
	~CommandTopic();

	void execute(IRCMessage msg, unsigned long client_id);
};
