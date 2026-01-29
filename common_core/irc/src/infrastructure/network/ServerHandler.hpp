/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 11:18:47 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 10:31:54 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "IReactorHandler.hpp"
#include "PollReactor.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "IClientRepository.hpp"
#include "CommandBus.hpp"
#include "ClientHandler.hpp"

class ServerHandler : public IReactorHandler
{

private:
	PollReactor &_pollReactor;
	IClientRepositoryPort &_clientRepo;
	CommandBus &_commandBus;

public:
	ServerHandler(PollReactor &pollReactor, IClientRepositoryPort &clientRepo, CommandBus &commandBus);
	~ServerHandler();

	void on_writable(int fd);
	void on_readable(int fd);
	void on_exitable(int fd);
	void on_error(int fd);
};
