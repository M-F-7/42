/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientStore.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:57:12 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 15:09:45 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientStore.hpp"

Client *ClientStore::newClient(int fd)
{
	Client *client = new Client();
	client->setClientFd(fd);
	client->setClientId(this->_nextId++);
	this->_clientsByFd.insert(std::make_pair(fd, client));
	this->_clientsById.insert(std::make_pair(client->getClientId(), client));
	return (client);
}

std::vector<Client *> ClientStore::getClients()
{
	std::vector<Client *> clients;
	std::map<unsigned long, Client *>::iterator it = this->_clientsById.begin();
	std::map<unsigned long, Client *>::iterator ite = this->_clientsById.end();
	for (; it != ite; it++)
		clients.push_back(it->second);
	return (clients);
}

Client *ClientStore::getClient(unsigned long id)
{
	std::map<unsigned long,
			 Client *>::iterator it = this->_clientsById.find(id);
	if (it != this->_clientsById.end())
		return (it->second);
	return (0);
}

Client *ClientStore::getClientByFd(int fd)
{
	std::map<int, Client *>::iterator it = this->_clientsByFd.find(fd);
	if (it != this->_clientsByFd.end())
		return (it->second);
	return (0);
}

bool ClientStore::delClient(unsigned long id)
{
	std::map<unsigned long,
			 Client *>::iterator it = this->_clientsById.find(id);
	if (it != this->_clientsById.end())
	{
		this->_clientsById.erase(it);
		return (true);
	}
	return (false);
}

bool ClientStore::delClientByFd(int fd)
{
	std::map<int, Client *>::iterator it = this->_clientsByFd.find(fd);
	if (it != this->_clientsByFd.end())
	{
		this->_clientsById.erase(it->second->getClientId());
		delete it->second;
		this->_clientsByFd.erase(it);
		return (true);
	}
	return (false);
}
