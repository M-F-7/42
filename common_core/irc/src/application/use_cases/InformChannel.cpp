/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InformChannel.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 13:46:45 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/30 19:00:01 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InformChannel.hpp"

InformChannel::InformChannel(IPublisher *publisher) : _publisher(*publisher) {};

void InformChannel::execute(Channel &channel, User *sender, const std::string &msg)
{
	std::map<User *, bool> users = channel.getUsers();
	std::map<User *, bool>::iterator it = users.begin();
	std::map<User *, bool>::iterator ite = users.end();

	for (; it != ite; it++)
	{
		if (sender && (*it).first->getId() == sender->getId())
			continue;
		Response res(*it->first);
		res.setMsg(msg);
		if (sender)
			res.setSender(*sender);
		this->_publisher.publish(res);
	}
}
