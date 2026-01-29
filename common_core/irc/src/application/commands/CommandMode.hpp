/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandMode.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:05:33 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/17 12:10:36 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IChannelRepository.hpp"
#include "UseCases.hpp"

class CommandMode : public ICommand
{
private:
	IUserRepositoryPort &userRepo;
	IChannelRepositoryPort &channelRepo;
	UseCases &useCases;

	void _displayModes(Channel &chan, User &user);
	void _handleModifications(Channel &chan, IRCMessage &msg);
	void _handleLimitModification(Channel &chan, std::string strLimit);
	void _informChanAboutModifications(Channel &chan, User &user, IRCMessage &msg);

public:
	CommandMode(IUserRepositoryPort &userRepo, UseCases &useCases, IChannelRepositoryPort &channelRepo);
	~CommandMode();

	void execute(IRCMessage msg, unsigned long client_id);
};
