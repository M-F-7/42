/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sender.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:02:52 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 16:08:55 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sys/socket.h>
#include "IClientRepository.hpp"

class Sender
{
	IClientRepositoryPort *clientRepo;

public:
	~Sender() {}
	Sender(IClientRepositoryPort *clientRepo);
	void sendMessage(unsigned long clientId, const std::string &data);
};
