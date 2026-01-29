/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketAcceptor.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:43:50 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/03 22:55:17 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketAcceptor.hpp"
#include <signal.h>

SocketAcceptor::SocketAcceptor(IReactorHandler *serverHandler, PollReactor &pollReactor)
	: _addr(), _sockfd(-1), _watched(false), _serverHandler(serverHandler), _pollReactor(pollReactor)
{
	_addr.sin6_family = AF_INET6;
	_addr.sin6_addr = in6addr_any;
	_addr.sin6_flowinfo = 0;
	_addr.sin6_scope_id = 0;
	_addr.sin6_port = htons(0);
};

SocketAcceptor::~SocketAcceptor()
{
	// Best-effort cleanup
	try
	{
		if (_watched && _sockfd >= 0)
			_pollReactor.unwatch(_sockfd);
	}
	catch (...)
	{
		// swallow
	}
	if (_sockfd >= 0)
		close(_sockfd);
};

void SocketAcceptor::start(unsigned int port)
{

	int off = 0;
	int on = 1;

	this->_sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (this->_sockfd < 0)
		throw NetworkException("[SocketAcceptor] Socket creation error");
	this->_addr.sin6_port = htons(port);

	if (setsockopt(this->_sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
	{
		close(this->_sockfd);
		this->_sockfd = -1;
		throw NetworkException("[SocketAcceptor] Setting SO_REUSEADDR failed");
	}
	if (setsockopt(this->_sockfd, IPPROTO_IPV6, IPV6_V6ONLY, &off, sizeof(off)) < 0)
	{
		close(this->_sockfd);
		this->_sockfd = -1;
		throw NetworkException("[SocketAcceptor] Setting IPV6_V6ONLY failed");
	}
	if (bind(this->_sockfd, reinterpret_cast<sockaddr *>(&_addr), sizeof(sockaddr_in6)) < 0)
	{
		close(this->_sockfd);
		this->_sockfd = -1;
		throw NetworkException("[SocketAcceptor] Binding socket");
	}
	if (listen(this->_sockfd, 16) < 0)
	{
		close(this->_sockfd);
		this->_sockfd = -1;
		throw NetworkException("[SocketAcceptor] Listening socket");
	}
	if (fcntl(this->_sockfd, F_SETFL, O_NONBLOCK) < 0)
	{
		close(this->_sockfd);
		this->_sockfd = -1;
		throw NetworkException("[SocketAcceptor] Fcntling");
	}
	this->_pollReactor.watch(this->_sockfd, POLLIN, this->_serverHandler);
	signal(SIGPIPE, SIG_IGN);
	this->_watched = true;
}
