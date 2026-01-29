/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 10:38:51 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/29 15:54:45 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "SocketAcceptor.hpp"
#include "Infrastructures.hpp"
#include "Adapters.hpp"

class TCPServer
{

private:
	SocketAcceptor &_socketAcceptor;
	PollReactor &_pollReactor;
	Infrastructures &_infra;

	void _cleanFagot(int client_fd);
	// void _removeFagotFromChannels(unsigned long clientID);

public:
	TCPServer(SocketAcceptor &socketAcceptor, PollReactor &pollReactor, Infrastructures &infra);
	~TCPServer();

	void start(unsigned int port);
};
