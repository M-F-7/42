/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNotice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:46:54 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 00:18:38 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include <IUserRepository.hpp>
#include <UseCases.hpp>
#include <IChannelRepository.hpp>

class CommandNotice : public ICommand
{
private:
	IUserRepositoryPort &_userRepo;
	UseCases &_usesCases;

	void _handleUsers(IRCMessage msg, User &currUser);

public:
	CommandNotice(IUserRepositoryPort &userRepo, UseCases &usesCases);
	~CommandNotice();

	void execute(IRCMessage msg, unsigned long client_id);
};
