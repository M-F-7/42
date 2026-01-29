/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandBus.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 09:36:12 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 15:44:23 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include "ICommand.hpp"
#include "CommandType.hpp"
#include "IPublisher.hpp"
#include "IUserRepository.hpp"
#include "IParser.hpp"

class CommandBus
{

private:
	std::map<CommandType, ICommand *> _commands;
	IParser *_parser;
	IPublisher &_publisher;
	IUserRepositoryPort &_userRepo;

public:
	CommandBus(IParser *parser, std::map<CommandType, ICommand *> cmd_lst, IPublisher &publisher, IUserRepositoryPort &userRepo);
	~CommandBus();

	void execute(std::string input, unsigned long client_id);
};
