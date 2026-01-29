/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:09:17 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 13:19:40 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

unsigned int ServerConfig::_port = 0;		   // av[1]
std::string ServerConfig::_password = "";	   // av[2]
std::string ServerConfig::_host = "irc.42.fr"; // av[2]
std::string ServerConfig::_startupTime = "";

unsigned int ServerConfig::getPort()
{
	return _port;
}

const std::string &ServerConfig::getPassword()
{
	return _password;
}

const std::string &ServerConfig::getHost()
{
	return _host;
}

void ServerConfig::setPort(unsigned int port)
{
	_port = port;
}

void ServerConfig::setPassword(const std::string &password)
{
	_password = password;
}


void ServerConfig::initStartupTime() {
    std::time_t now = std::time(0);
    char* timeStr = std::ctime(&now);
    _startupTime = std::string(timeStr);
    if (!_startupTime.empty() && _startupTime[_startupTime.length() - 1] == '\n') {
        _startupTime.erase(_startupTime.length() - 1);
    }
}

const std::string& ServerConfig::getStartupTime() {
    return _startupTime;
}