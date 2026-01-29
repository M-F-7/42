/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserStore.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:50:15 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/01 10:06:31 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserStore.hpp"

// ********************************** //
// ** Constructors and Destructors ** //
// ********************************** //

UserStore::UserStore() {};
UserStore::~UserStore() {};

// *********************** //
// ** Members Functions ** //
// *********************** //

User &UserStore::getOrCreate(unsigned long id)
{
	std::map<unsigned long, User>::iterator it = this->_users.find(id);
	if (it == this->_users.end())
		return this->addUser(id);
	return it->second;
}

User &UserStore::addUser(unsigned long id)
{
	this->_users.insert(std::make_pair(id, User(id)));
	return (this->_users.find(id)->second);
}

bool UserStore::delUser(unsigned long id)
{
	return this->_users.erase(id);
}

User *UserStore::getByNickName(const std::string &nickName)
{
	std::map<unsigned long, User>::iterator it = this->_users.begin();
	std::map<unsigned long, User>::iterator ite = this->_users.end();

	for (; it != ite; it++)
		if (it->second.getNickName() == nickName)
			return &it->second;
	return NULL;
}
