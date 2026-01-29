/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:27:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 15:56:57 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandJoin.hpp"
#include "CommandKick.hpp"
#include "CommandNick.hpp"
#include "CommandPart.hpp"
#include "CommandPass.hpp"
#include "CommandQuit.hpp"
#include "CommandUser.hpp"
#include "CommandPrivMsg.hpp"
#include "CommandNotice.hpp"
#include "CommandTopic.hpp"
#include "CommandInvite.hpp"
#include "CommandMode.hpp"
#include "CommandCap.hpp"
#include "CommandBot.hpp"
#include "Commands.hpp"
#include "CommandPing.hpp"

Commands::Commands(Infrastructures &infra, Adapters &adapters, UseCases &useCases)
{
	commandMap[JOIN] = new CommandJoin(*infra.userRepo, *infra.channelRepo, useCases);
	commandMap[NICK] = new CommandNick(*infra.userRepo, *adapters.publisher);
	commandMap[KICK] = new CommandKick(*infra.channelRepo, *infra.userRepo, *adapters.publisher);
	commandMap[PART] = new CommandPart(*infra.userRepo, *adapters.publisher, *infra.channelRepo);
	commandMap[PASS] = new CommandPass(*infra.userRepo);
	commandMap[USER] = new CommandUser(*infra.userRepo, *adapters.publisher);
	commandMap[QUIT] = new CommandQuit(*infra.userRepo, *useCases.informChannel, *infra.channelRepo, *useCases.disconnectUser);
	commandMap[PRIVMSG] = new CommandPrivMsg(*infra.userRepo, useCases, *infra.channelRepo);
	commandMap[NOTICE] = new CommandNotice(*infra.userRepo, useCases);
	commandMap[TOPIC] = new CommandTopic(*infra.userRepo, useCases, *infra.channelRepo);
	commandMap[INVITE] = new CommandInvite(*infra.userRepo, useCases, *infra.channelRepo);
	commandMap[MODE] = new CommandMode(*infra.userRepo, useCases, *infra.channelRepo);
	commandMap[CAP] = new CommandCap(*infra.userRepo, useCases);
	commandMap[BOT] = new CommandBot(*infra.userRepo, useCases);
	commandMap[PING] = new CommandPing(*infra.userRepo, useCases);
	commandBus = new CommandBus(infra.parser, commandMap, *adapters.publisher, *infra.userRepo);
}

Commands::~Commands()
{
	std::map<CommandType, ICommand *>::iterator it = commandMap.begin();
	std::map<CommandType, ICommand *>::iterator ite = commandMap.end();

	for (; it != ite; ++it)
		if (it->second)
			delete it->second;
	if (commandBus)
		delete commandBus;
}
