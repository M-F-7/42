/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Networks.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 21:59:17 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 16:14:15 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "TCPServer.hpp"
#include "ServerConfig.hpp"
#include "CommandBus.hpp"

class Networks
{
public:
	TCPServer *server;
	SocketAcceptor *socketAcceptor;
	IReactorHandler *serverHandler;
	IReactorHandler *clientHandler;

	Networks(Infrastructures &infra, CommandBus &commandBus);
	~Networks();
};
