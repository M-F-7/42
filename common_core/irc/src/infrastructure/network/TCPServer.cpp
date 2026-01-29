/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:39:33 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/01 10:10:39 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCPServer.hpp"

TCPServer::TCPServer(SocketAcceptor &socketAcceptor, PollReactor &pollReactor, Infrastructures &infra) : _socketAcceptor(socketAcceptor), _pollReactor(pollReactor), _infra(infra) {};
TCPServer::~TCPServer() {};

void TCPServer::start(unsigned int port)
{
	try
	{
		this->_socketAcceptor.start(port);
		for (;;)
		{
			try
			{
				this->_pollReactor.loop_once(50);
			}
			
			catch (ClientAUREVOIRByFd &e)
			{
				Client *clicli = _infra.clientRepo->getClientByFd(e.fd);
				if (!clicli)
					continue;
				this->_infra.pollReactor.unwatch(clicli->getClientFd());
				this->_infra.clientRepo->delClientByFd(clicli->getClientFd());
			}
			catch (ClientAUREVOIRById &e)
			{
				Client *clicli = _infra.clientRepo->getClient(e.id);
				if (!clicli)
					continue;
				this->_infra.pollReactor.unwatch(clicli->getClientFd());
				this->_infra.clientRepo->delClientByFd(clicli->getClientFd());
			}
			catch (std::exception &e)
			{  
				std::cout << e.what() << std::endl;
			}	
		}
	}
	catch (const NetworkException &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
