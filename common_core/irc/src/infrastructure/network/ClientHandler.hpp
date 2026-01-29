/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:29:08 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 14:38:26 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IReactorHandler.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include "NetworkException.hpp"
#include "CommandBus.hpp"
#include <deque>

class ClientHandler : public IReactorHandler
{

private:
	CommandBus &_commandBus;
	std::string _readin_buffer;
	unsigned long _clientID;
	std::deque<std::string> _waiting_msgs;

public:
	ClientHandler(CommandBus &commandBus, unsigned long clientId);
	~ClientHandler();

	void on_writable(int fd);
	void on_readable(int fd);
	void on_exitable(int fd);
	void on_error(int fd);

	unsigned long getClientId() const;
};
