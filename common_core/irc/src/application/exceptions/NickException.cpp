/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickException.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:38:40 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/17 17:17:59 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickException.hpp"

NickException::NickException(std::string nick, StatusCode status, std::string msg) : StatusException(), _nick(nick)
{
	std::string finalMsg;

	finalMsg += nick + " :" + msg;
	this->setMsg(finalMsg);
	this->setStatus(status);
}
NickException::~NickException() throw() {};

NickNameAlreadyUsedException::NickNameAlreadyUsedException(std::string nick) : NickException(nick, ERR_NICKNAMEINUSE, "Nickname is already in use") {}
NickNameAlreadyUsedException::~NickNameAlreadyUsedException() throw() {};

NoNickNameGivenException::NoNickNameGivenException() : NickException("", ERR_NONICKNAMEGIVEN, "No nickname given") {}
NoNickNameGivenException::~NoNickNameGivenException() throw() {};

NickNameInvalid::NickNameInvalid(std::string nick) : NickException(nick, ERR_ERRONEUSNICKNAME, "Erroneus nickname") {}
NickNameInvalid::~NickNameInvalid() throw() {};
