/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserStore.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:45:04 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/13 16:57:42 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "User.hpp"
#include <iostream>
#include <map>
#include "IUserRepository.hpp"

class UserStore : public IUserRepositoryPort
{
private:
	std::map<unsigned long, User> _users;

	User &addUser(unsigned long id);

public:
	UserStore();
	~UserStore();

	User &getOrCreate(unsigned long id);
	bool delUser(unsigned long id);
	User *getByNickName(const std::string &nickName);
};
