/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollReactor.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 08:50:59 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 10:15:46 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <poll.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <cstring>
#include "IReactorHandler.hpp"
#include "NetworkException.hpp"

class PollReactor
{
private:
	std::vector<pollfd> _fds;
	std::vector<IReactorHandler *> _handlers;

	void _handle_revents(pollfd &pfd, IReactorHandler &handler);
	void _handle_err_events(pollfd &pfd, IReactorHandler &handler);

	struct DispatchItem
	{
		int fd;
		short revents;
		IReactorHandler *handler;
	};

public:
	PollReactor();
	~PollReactor();

	void watch(int fd, short events, IReactorHandler *handler);
	void unwatch(int fd);
	void loop_once(unsigned int ms);
};
