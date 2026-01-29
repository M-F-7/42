/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandNick.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 10:48:21 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 13:47:13 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IPublisher.hpp"
#include "ServerConfig.hpp"

class CommandNick : public ICommand
{
private:
	IUserRepositoryPort &_userRepo;
	IPublisher &_publisher;

	std::string _formatMessage(User &user, std::string newNick);
	void _sendWelcome(Response &res);

public:
	CommandNick(IUserRepositoryPort &userRepo, IPublisher &publisher);
	~CommandNick();

	void execute(IRCMessage msg, unsigned long client_id);
};
