/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollReactor.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:06:50 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/02 15:50:27 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollReactor.hpp"

PollReactor::PollReactor() {};

PollReactor::~PollReactor() {}

// ** *********************** ** ??
// ** Public Member Functions ** ??
// ** *********************** ** ??

void PollReactor::watch(int fd, short events, IReactorHandler *handler)
{
	pollfd pfd;

	if (fd < 3)
		throw NetworkException("[PollReactor] can't watch fd less than 3.");
	for (size_t i = 0; i < this->_fds.size(); i++)
		if (this->_fds[i].fd == fd)
			throw NetworkException("[PollReactor] fd already watch.");
	pfd.fd = fd;
	pfd.events = events;
	pfd.revents = 0;
	this->_fds.push_back(pfd);
	this->_handlers.push_back(handler);
}

void PollReactor::unwatch(int fd)
{
	if (fd < 3)
		throw NetworkException("[PollReactor] can't unwatch fd less than 3.");
	for (size_t i = 0; i < this->_fds.size(); i++)
	{
		if (this->_fds[i].fd != fd)
			continue;
		if (fd > 2)
			close(fd);
		this->_fds.erase(this->_fds.begin() + i);
		this->_handlers.erase(this->_handlers.begin() + i);
		return;
	}

	std::ostringstream oss;
	oss << "[PollReactor] fd " << fd << " doesn't watch.";
	throw NetworkException(oss.str());
}

void PollReactor::loop_once(unsigned int ms)
{
	int res = poll(this->_fds.data(), this->_fds.size(), ms);

	if (res == 0)
		return;
	if (res < 0)
	{
		std::ostringstream oss;
		oss << "[PollReactor] polling error: " << std::strerror(errno) << std::endl;
		throw NetworkException(oss.str());
	}

	std::vector<DispatchItem> toDispatch;
	toDispatch.reserve(this->_fds.size());

	for (size_t i = 0; i < this->_fds.size(); ++i)
	{
		if (this->_fds[i].revents == 0)
			continue;
		DispatchItem s;
		s.fd = this->_fds[i].fd;
		s.revents = this->_fds[i].revents;
		s.handler = this->_handlers[i];
		toDispatch.push_back(s);
	}

	for (size_t i = 0; i < toDispatch.size(); ++i)
	{
		pollfd p;
		p.fd = toDispatch[i].fd;
		p.events = 0;
		p.revents = toDispatch[i].revents;
		this->_handle_revents(p, *toDispatch[i].handler);
	}
};

void PollReactor::_handle_revents(pollfd &pfd, IReactorHandler &handler)
{
	bool is_error = false;

	if (pfd.revents & POLLIN)
		handler.on_readable(pfd.fd);
	if (pfd.revents & POLLOUT)
		handler.on_writable(pfd.fd);

	if (pfd.revents & (POLLHUP | POLLRDHUP))
		handler.on_exitable(pfd.fd);
	if (pfd.revents & (POLLERR | POLLNVAL))
		is_error = true;

	if (!is_error)
		return;

	this->_handle_err_events(pfd, handler);
}

void PollReactor::_handle_err_events(pollfd &pfd, IReactorHandler &handler)
{
	handler.on_error(pfd.fd);

	int fd = pfd.fd;
	for (size_t i = 0; i < this->_fds.size(); i++)
	{
		if (this->_fds[i].fd != pfd.fd)
			continue;
		this->_fds.erase(this->_fds.begin() + i);
		this->_handlers.erase(this->_handlers.begin() + i);
		return;
	}
	std::ostringstream oss;
	oss << "[PollReactor] fd " << fd << " not found 🤯." << std::endl;
	throw NetworkException(oss.str());
}
