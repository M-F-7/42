/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NetworkException.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 09:16:01 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 14:51:23 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NetworkException.hpp"

NetworkException::NetworkException(std::string msg)
{
	this->_msg = msg + " : " + std::string(strerror(errno));
}

NetworkException::~NetworkException() throw() {};

const char *NetworkException::what() const throw()
{
	return (_msg.c_str());
}

ClientAUREVOIRByFd::ClientAUREVOIRByFd(int fd) : fd(fd)
{
	this->mgs = "Client bye bye!";
}

ClientAUREVOIRByFd::~ClientAUREVOIRByFd() throw() {};

const char *ClientAUREVOIRByFd::what() const throw()
{
	return (mgs.c_str());
}

ClientAUREVOIRById::ClientAUREVOIRById(unsigned long id) : id(id)
{
}

ClientAUREVOIRById::~ClientAUREVOIRById() throw()
{
}

const char *ClientAUREVOIRById::what() const throw()
{
	return "OUAI OUAI";
}
