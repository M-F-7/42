/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:20:03 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 11:02:21 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerHandler.hpp"

ServerHandler::ServerHandler(PollReactor &pollReactor, IClientRepositoryPort &clientRepo, CommandBus &commandBus) : _pollReactor(pollReactor), _clientRepo(clientRepo), _commandBus(commandBus) {};
ServerHandler::~ServerHandler() {};

void ServerHandler::on_writable(int)
{
	throw NetworkException("[ServerHandler] should never see this fucking exception! 🤦");
}

void ServerHandler::on_readable(int fd)
{
	int clientFd = accept(fd, NULL, NULL);
	short events = POLLIN | POLLOUT;

	if (clientFd < 3)
		throw NetworkException("[ServerHandler] accepting client");
	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0)
		throw NetworkException("[ServerHandler] Fcntling error");
	Client *tom = this->_clientRepo.newClient(clientFd);
	tom->setClientHandler(new ClientHandler(this->_commandBus, tom->getClientId()));
	this->_pollReactor.watch(clientFd, events, tom->getClientHandler());
}

void ServerHandler::on_error(int)
{
	throw NetworkException("[ServerHandler] on error");
}

void ServerHandler::on_exitable(int)
{
	throw NetworkException("[ServerHandler] on exitable");
}
