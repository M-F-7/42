/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandUser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 09:22:38 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 13:40:33 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ICommand.hpp"
#include "IUserRepository.hpp"
#include "IPublisher.hpp"
#include "ServerConfig.hpp"

class CommandUser : public ICommand
{
private:
	IUserRepositoryPort &_userRepo;
	IPublisher &_publisher;

	std::string _formatMessage(User &user);
	void _sendWelcome(Response &res);

public:
	CommandUser(IUserRepositoryPort &userRepo, IPublisher &publisher);
	~CommandUser();

	void execute(IRCMessage msg, unsigned long client_id);
};
