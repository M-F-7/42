/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:30:32 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/30 16:01:39 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

User::User(unsigned long id) : _id(id), _isLog(DISCONNECTED) {};

User::~User() {};

User &User::operator=(const User &other)
{
	if (this == &other)
		return *this;
	this->_username = other._username;
	this->_nickname = other._nickname;
	this->_isLog = other._isLog;
	return *this;
}

void User::setUserName(std::string name)
{
	this->_username = name;
}
void User::setNickName(std::string nickname)
{
	this->_nickname = nickname;
}
void User::setIsLogConnected()
{
	this->_isLog = CONNECTED;
}

void User::setIsLogIdentified()
{
	if (!this->_username.empty() && !this->_nickname.empty())
		this->_isLog = IDENTIFIED;
}

std::string User::getUserName() const
{
	return (this->_username);
}
std::string User::getNickName() const
{
	return (this->_nickname);
}

User::state User::getIsLog() const
{
	return (this->_isLog);
}

unsigned long User::getId() const
{
	return (this->_id);
}
