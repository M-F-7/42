/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 09:30:35 by mfernand          #+#    #+#             */
/*   Updated: 2025/09/17 15:46:33 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "NickException.hpp"

class User
{
public:
	enum state
	{
		IDENTIFIED = 1,
		DISCONNECTED,
		CONNECTED,
	};

private:
	const unsigned long _id; // belek
	std::string _username;
	std::string _nickname;
	state _isLog;

public:
	User(unsigned long id);
	~User();

	User &operator=(const User &other);

	void setUserName(std::string name);
	void setNickName(std::string nickname);
	void setIsLogConnected();
	void setIsLogIdentified();

	std::string getUserName() const;
	std::string getNickName() const;
	state getIsLog() const;
	unsigned long getId() const;
};
