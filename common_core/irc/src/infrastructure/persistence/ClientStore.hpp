/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientStore.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:47:54 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 11:20:11 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include "IClientRepository.hpp"

class ClientStore : public IClientRepositoryPort
{
private:
	std::map<unsigned long, Client *> _clientsById;
	std::map<int, Client *> _clientsByFd;
	unsigned long _nextId;

public:
	Client *newClient(int fd);

	std::vector<Client *> getClients();
	Client *getClient(unsigned long id);
	Client *getClientByFd(int fd);
	bool delClient(unsigned long id);
	bool delClientByFd(int fd);
};
