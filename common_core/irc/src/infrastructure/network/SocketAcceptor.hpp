/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketAcceptor.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:44:03 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 10:06:33 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "IReactorHandler.hpp"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "NetworkException.hpp"
#include "PollReactor.hpp"

class SocketAcceptor
{
private:
	struct sockaddr_in6 _addr;
	int _sockfd;
	bool _watched;
	IReactorHandler *_serverHandler;
	PollReactor &_pollReactor;

public:
	SocketAcceptor(IReactorHandler *serverHandler, PollReactor &pollReactor);
	~SocketAcceptor();

	void start(unsigned int port);
};
