/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:05:18 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 22:57:00 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sender.hpp"

Sender::Sender(IClientRepositoryPort *clientRepo) : clientRepo(clientRepo) {}

void Sender::sendMessage(unsigned long clientId, const std::string &data)
{
	Client *client = clientRepo->getClient(clientId);

	if (!client)
		return;
	send(client->getClientFd(), data.c_str(), data.size(), MSG_NOSIGNAL);
}
