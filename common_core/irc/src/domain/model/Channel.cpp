/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:49:19 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/02 15:49:44 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name) : _name(name)
{
	this->_limit = 0;
	this->_inviteOnly = 0;
	this->_TopicLock = 0;
	this->_nbUsers = 0;
}
Channel::~Channel() {};

Channel &Channel::operator=(const Channel &other)
{
	if (this == &other)
		return (*this);
	this->_nbUsers = other._nbUsers;
	this->_limit = other._limit;
	this->_pass = other._pass;
	this->_theme = other._theme;
	this->_inviteOnly = other._inviteOnly;
	this->_TopicLock = other._TopicLock;
	return (*this);
}

void Channel::giveOperator(std::string nick)
{
	std::map<User *, bool>::iterator it = this->_users.begin();
	std::map<User *, bool>::iterator ite = this->_users.end();

	for (; it != ite; it++)
	{
		if (!it->first->getNickName().compare(nick))
		{
			it->second = true;
			return;
		}
	}
}

void Channel::removeOperator(std::string nick)
{
	std::map<User *, bool>::iterator it = this->_users.begin();
	std::map<User *, bool>::iterator ite = this->_users.end();

	for (; it != ite; it++)
	{
		if (!it->first->getNickName().compare(nick))
		{
			it->second = false;
			return;
		}
	}
}

bool Channel::isOperator(User &user)
{
	std::map<User *, bool>::iterator it = this->_users.find(&user);
	if (it == this->_users.end())
		return false;
	return it->second;
}

// ************* //
// ** Setters ** //
// ************* //

void Channel::setNbUsers(unsigned long nb)
{
	this->_nbUsers = nb;
}
void Channel::setLimit(unsigned long nb)
{
	this->_limit = nb;
}
void Channel::setPass(std::string password)
{
	this->_pass = password;
}
void Channel::setTheme(std::string theme)
{
	if (this->_TopicLock)
		throw Exceptions::NotPermTheme();
	this->_theme = theme;
}
void Channel::setInviteOnly(bool state)
{
	this->_inviteOnly = state;
}
void Channel::setTopicLock(bool state)
{
	this->_TopicLock = state;
}


// ************* //
// ** Getters ** //
// ************* //

unsigned long Channel::getNbUsers() const
{
	return (this->_nbUsers);
}
unsigned long Channel::getLimit() const
{
	return (this->_limit);
}
std::string Channel::getPass() const
{
	return (this->_pass);
}

std::string Channel::getName() const
{
	return this->_name;
}

std::string Channel::getTheme() const
{
	return (this->_theme);
}
bool Channel::getInviteOnly() const
{
	return (this->_inviteOnly);
}
bool Channel::getTopicLock() const
{
	return (this->_TopicLock);
}
bool Channel::getPassUp() const
{
	return this->_pass.size();
}

bool Channel::getIsLimited() const
{
	return this->_limit > 0;
}

std::map<User *, bool> &Channel::getUsers()
{
	return this->_users;
}

bool Channel::isInUsers(std::string &nick)
{
	std::map<User *, bool>::iterator it = this->_users.begin();
	std::map<User *, bool>::iterator ite = this->_users.end();
	for (; it != ite; it++)
		if (!it->first->getNickName().compare(nick))
			return true;
	return false;
}

bool Channel::isInUsers(User &user)
{
	return this->_users.find(&user) != this->_users.end();
}

bool Channel::isInvited(const std::string &nick)
{
	for (size_t i = 0; i < this->_invitedUsers.size(); i++)
		if (!this->_invitedUsers[i]->getNickName().compare(nick))
			return true;
	return false;
}

bool Channel::isBanned(const std::string &nick)
{
	for (size_t i = 0; i < this->_bannedUsers.size(); i++)
		if (!this->_bannedUsers[i]->getNickName().compare(nick))
			return true;
	return false;
}

void Channel::addUser(User &user)
{
	std::map<User *, bool>::iterator itUser = this->_users.find(&user);
	if (itUser != this->_users.end())
		return;
	if (!this->_users.size())
		this->_users.insert(std::make_pair(&user, true));
	else
		this->_users.insert(std::make_pair(&user, false));
	this->_nbUsers++;
}

void Channel::deleteUser(std::string &nick)
{
	std::map<User *, bool>::iterator it = this->_users.begin();
	std::map<User *, bool>::iterator ite = this->_users.end();
	for (; it != ite; it++)
	{
		if (!it->first->getNickName().compare(nick))
		{
			this->_users.erase(it);
			this->_nbUsers--;
			return;
		}
	}
}

void Channel::deleteUser(User &user)
{
	std::map<User *, bool>::iterator itUser = this->_users.find(&user);
	if (itUser == this->_users.end())
		return;
	this->_users.erase(itUser);
	this->_nbUsers--;
}

void Channel::deleteInvitedUser(User &user)
{
	std::vector<User *>::iterator it = this->_invitedUsers.begin();
	std::vector<User *>::iterator ite = this->_invitedUsers.end();

	for (; it < ite; it++)
	{
		if (*it == &user)
		{
			this->_invitedUsers.erase(it);
			return;
		}
	}
}
void Channel::deleteBannedUser(User &user)
{
	std::vector<User *>::iterator it = this->_bannedUsers.begin();
	std::vector<User *>::iterator ite = this->_bannedUsers.end();

	for (; it < ite; it++)
	{
		if (*it == &user)
		{
			this->_bannedUsers.erase(it);
			return;
		}
	}
}

void Channel::addBanned(User &user)
{
	this->deleteUser(user);
	this->deleteInvitedUser(user);
	if (!this->isBanned(user.getNickName()))
		this->_bannedUsers.push_back(&user);
}

void Channel::addInvited(User &user)
{
	if (!this->isInvited(user.getNickName()))
		this->_invitedUsers.push_back(&user);
}
