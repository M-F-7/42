/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkException.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwassim <rwassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:10:39 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/02 10:30:04 by rwassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <string>
#include <cerrno>
#include <cstring>
#include "CommandType.hpp"

class NetworkException : public std::exception
{
private:
	std::string _msg;

public:
	NetworkException(std::string msg);
	virtual ~NetworkException() throw();

	virtual const char *what() const throw();
};

class ClientAUREVOIRByFd : public std::exception
{
private:
	std::string mgs;

public:
	int fd;
	ClientAUREVOIRByFd(int fd);
	virtual ~ClientAUREVOIRByFd() throw();

	virtual const char *what() const throw();
};

class ClientAUREVOIRById : public std::exception
{
private:
	std::string mgs;

public:
	int id;
	ClientAUREVOIRById(unsigned long id);
	virtual ~ClientAUREVOIRById() throw();

	virtual const char *what() const throw();
};
