/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 11:47:53 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/13 20:34:56 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StatusException.hpp"

StatusException::StatusException() {};
StatusException::StatusException(const StatusCode status, std::string msg) : _status(status), _msg(msg) {}
StatusException::~StatusException() throw() {};

StatusCode StatusException::getStatus() const
{
	return this->_status;
};

const char *StatusException::what() const throw()
{
	if (!this->_msg.empty())
		return this->_msg.c_str();
	return "Exception message is missing...";
};

void StatusException::setStatus(StatusCode status)
{
	this->_status = status;
};

void StatusException::setMsg(std::string &msg)
{
	this->_msg = msg;
};
