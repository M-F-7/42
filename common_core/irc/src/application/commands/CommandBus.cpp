/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandBus.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:38:17 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 13:32:54 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandBus.hpp"
#include "StatusException.hpp"
#include "NotConnected.hpp"
#include "NetworkException.hpp"

CommandBus::CommandBus(IParser *parser, std::map<CommandType, ICommand *> cmd_lst, IPublisher &publisher, IUserRepositoryPort &userRepo) : _commands(cmd_lst), _parser(parser), _publisher(publisher), _userRepo(userRepo) {};

CommandBus::~CommandBus()
{
	// dont delete commands->second, already deleted in Commands.cpp
	this->_commands.clear();
};

void CommandBus::execute(std::string input, unsigned long client_id)
{

	User &currentUser = this->_userRepo.getOrCreate(client_id);
	Response response(currentUser);

	try
	{
		IRCMessage commandCtx = this->_parser->parseMessage(input);
		std::map<CommandType, ICommand *>::iterator cmd = this->_commands.find(commandCtx.command);

		if (cmd == this->_commands.end())
		{
			response.setStatusCode(ERR_UNKNOWNCOMMAND);
			response.setMsg("421 " + commandCtx.reason + " :Unknown command");
			this->_publisher.publish(response);
			return;
		}
		
		if (commandCtx.command == QUIT || commandCtx.command == CAP)
			return cmd->second->execute(commandCtx, client_id);
		else if (commandCtx.command == USER ||  commandCtx.command == NICK)
		{
			if (currentUser.getIsLog() == User::DISCONNECTED)
				throw NotConnected(commandCtx.command);
		}
		// else if (commandCtx.command == USER){
		// 	if (currentUser.getIsLog() == User::DISCONNECTED)
		// 		throw NotConnected(commandCtx.command);
		// 	if (currentUser.getNickName().empty())
		// 		throw NoNickNameGivenException();
		// }
		// else if( commandCtx.command == NICK){
		// 	if (currentUser.getIsLog() == User::DISCONNECTED)
		// 		throw NotConnected(commandCtx.command);
		// }
		else if (commandCtx.command != USER && commandCtx.command != NICK && commandCtx.command != PASS){
			if (currentUser.getIsLog() != User::IDENTIFIED)
				throw NotConnected(commandCtx.command);
		}
		cmd->second->execute(commandCtx, client_id);
	}
	catch (const StatusException &e)
	{
		response.setStatusCode(e.getStatus());
		response.setMsg(e.what());
		this->_publisher.publish(response);
	}
}
