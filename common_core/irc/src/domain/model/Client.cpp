/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:50:06 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 03:07:54 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _clientFd(-1), _clientId(0), _clientHandler(0) {};

Client::~Client() {};

void Client::setClientFd(int fd)
{
	this->_clientFd = fd;
}

int Client::getClientFd() const
{
	return this->_clientFd;
}

void Client::setClientId(unsigned long id)
{
	this->_clientId = id;
}

unsigned long Client::getClientId() const
{
	return this->_clientId;
}

void Client::setClientHandler(IReactorHandler *handler)
{
	this->_clientHandler = handler;
}

IReactorHandler *Client::getClientHandler() const
{
	return this->_clientHandler;
}

void Client::addMessage(std::string &msg)
{
	this->_waiting_msgs.push_back(msg);
}

std::vector<std::string> &Client::getMessages()
{
	return (this->_waiting_msgs);
}
