/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 02:50:03 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/14 03:16:05 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IReactorHandler.hpp"
#include <vector>
#include <string>

class Client
{
private:
	int _clientFd;
	unsigned long _clientId;
	IReactorHandler *_clientHandler;
	std::vector<std::string> _waiting_msgs;

public:
	Client();
	~Client();

	void setClientFd(int fd);
	int getClientFd() const;
	void setClientId(unsigned long id);
	unsigned long getClientId() const;
	void setClientHandler(IReactorHandler *handler);
	IReactorHandler *getClientHandler() const;
	void addMessage(std::string &msg);
	std::vector<std::string> &getMessages();
};
