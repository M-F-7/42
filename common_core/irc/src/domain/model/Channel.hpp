/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:36:24 by mfernand          #+#    #+#             */
/*   Updated: 2025/10/02 15:49:48 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <exception>
#include "Exceptions.hpp"
#include <map>
#include <vector>
#include "User.hpp"

class Channel
{
private:
	const std::string _name;
	unsigned long _limit;
	std::string _pass;
	bool _inviteOnly; //-i
	bool _TopicLock;  //-t
	std::string _theme;
	std::map<User *, bool> _users;
	std::vector<User *> _invitedUsers;
	std::vector<User *> _bannedUsers;
	unsigned long _nbUsers;

public:
	Channel(std::string name);
	~Channel();
	Channel &operator=(const Channel &other);

	void giveOperator(std::string nick);
	void removeOperator(std::string nick);
	bool isOperator(User &user);

	// seters and geters

	void setNbUsers(unsigned long nb);
	void setLimit(unsigned long nb);
	void setPass(std::string password);
	void setTheme(std::string theme);
	void setInviteOnly(bool state);
	void setTopicLock(bool state);

	unsigned long getNbUsers() const;
	unsigned long getLimit() const;
	std::string getName() const;
	std::string getPass() const;
	std::string getTheme() const;
	bool getInviteOnly() const;
	bool getTopicLock() const;
	bool getPassUp() const;
	bool getIsLimited() const;
	std::map<User *, bool> &getUsers();

	bool isInUsers(std::string &nick);
	bool isInUsers(User &user);
	bool isInvited(const std::string &nick);
	bool isBanned(const std::string &nick);

	void addUser(User &user);
	void addBanned(User &user);
	void addInvited(User &user);

	void deleteUser(std::string &nick);
	void deleteUser(User &user);
	void deleteInvitedUser(User &user);
	void deleteBannedUser(User &user);
};
