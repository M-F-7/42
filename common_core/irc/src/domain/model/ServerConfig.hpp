/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:07:15 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/03 13:19:04 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <ctime>
#include <string>

class ServerConfig
{

private:
	static unsigned int _port;	  // = av[1];
	static std::string _password; // = av[2];
	static std::string _host;
	static std::string _startupTime;

public:
	static void setPort(unsigned int port);
	static void setPassword(const std::string &password);
	static unsigned int getPort();
	static const std::string &getPassword();
	static const std::string &getHost();
    static void initStartupTime();
    static const std::string& getStartupTime();
};
