/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Networks.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:00:31 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 16:14:08 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Networks.hpp"
#include "ServerHandler.hpp"

Networks::Networks(Infrastructures &infra, CommandBus &commandBus)
{
	serverHandler = new ServerHandler(infra.pollReactor, *infra.clientRepo, commandBus);
	socketAcceptor = new SocketAcceptor(serverHandler, infra.pollReactor);
	server = new TCPServer(*socketAcceptor, infra.pollReactor, infra);
}

Networks::~Networks()
{
	if (serverHandler)
		delete serverHandler;
	if (socketAcceptor)
		delete socketAcceptor;
	if (server)
		delete server;
}
