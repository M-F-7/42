/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IClientRepository.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:49:28 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 11:20:03 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Client.hpp"
#include <vector>

class IClientRepositoryPort
{
public:
	virtual Client *newClient(int fd) = 0;
	virtual std::vector<Client *> getClients() = 0;
	virtual Client *getClient(unsigned long id) = 0;
	virtual Client *getClientByFd(int fd) = 0;
	virtual bool delClient(unsigned long id) = 0;
	virtual bool delClientByFd(int fd) = 0;
	virtual ~IClientRepositoryPort() {};
};
