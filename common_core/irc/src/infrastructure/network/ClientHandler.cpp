/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:30:43 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 22:59:02 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "ClientHandler.hpp"

ClientHandler::ClientHandler(CommandBus &commandBus,
							 unsigned long clientId) : _commandBus(commandBus), _clientID(clientId) {};
ClientHandler::~ClientHandler() {};

void ClientHandler::on_writable(int fd)
{
	if (this->_waiting_msgs.empty())
		return;
	std::string &msg = *this->_waiting_msgs.begin();
	if (send(fd, msg.c_str(), msg.size(), MSG_NOSIGNAL) < 0)
		throw NetworkException("[ClientManager] sending message");
	this->_waiting_msgs.pop_front();
}

void ClientHandler::on_readable(int fd)
{
	char buffer[1024];
	unsigned int rest;
	ssize_t bytes_recv;

	rest = 1024 - this->_readin_buffer.size();
	bytes_recv = recv(fd, buffer, rest - 1, 0);
	if (bytes_recv < 0)
		throw NetworkException("[ClientHandler] receiving message");
	if (bytes_recv == 0)
		throw ClientAUREVOIRByFd(fd);
	buffer[bytes_recv] = 0;
	this->_readin_buffer.append(buffer);
	for (;;)
	{
		size_t pos_crlf = this->_readin_buffer.find("\r\n");
		if (pos_crlf == std::string::npos)
			break;
		std::string cmd = this->_readin_buffer.substr(0, pos_crlf);
		this->_readin_buffer = this->_readin_buffer.substr(pos_crlf + 2);
		this->_commandBus.execute(cmd, this->getClientId());
	}
}

void ClientHandler::on_exitable(int fd)
{
	throw ClientAUREVOIRByFd(fd);
}

void ClientHandler::on_error(int fd)
{
	// throw ClientAUREVOIRByFd(fd);
	(void)fd;
}

unsigned long ClientHandler::getClientId() const
{
	return (this->_clientID);
}
