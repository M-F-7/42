/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 09:03:49 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/17 16:07:12 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(const User &dest) : _statusCode(NONE), _target(dest) {};
Response::Response(const User &dest, std::string &message) : _statusCode(NONE), _msg(message), _target(dest) {};
Response::Response(const User &dest, std::string &message, StatusCode statut) : _statusCode(statut), _msg(message), _target(dest) {};
Response::Response(const User &dest, std::string &message, StatusCode statut, User *sender) : _statusCode(statut), _msg(message), _sender(sender), _target(dest) {};
Response::~Response() {};

void Response::setStatusCode(StatusCode statut)
{
	this->_statusCode = statut;
}

void Response::setMsg(const std::string &message)
{
	this->_msg = message;
}

void Response::setSender(const User &other)
{
	this->_sender = const_cast<User *>(&other);
}
StatusCode Response::getStatusCode() const
{
	return (this->_statusCode);
}
std::string Response::getMsg() const
{
	return (this->_msg);
}

User *Response::getSender() const
{
	return (this->_sender);
}

const User &Response::getTarget() const
{
	return (this->_target);
}
