/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelStore.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:01:14 by dcastor           #+#    #+#             */
/*   Updated: 2025/10/01 10:05:31 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChannelStore.hpp"

// ********************************** //
// ** Constructors and Destructors ** //
// ********************************** //

ChannelStore::ChannelStore(){};
ChannelStore::~ChannelStore(){};

// *********************** //
// ** Members Functions ** //
// *********************** //

std::vector<Channel *> ChannelStore::getChannels()
{
	std:: vector<Channel*> channels;
	std:: map<std::string, Channel>::iterator it = this->_channels.begin();
	std:: map<std::string, Channel>::iterator ite = this->_channels.end();

	for (; it != ite; it++)
		channels.push_back(&it->second);
	return channels;
}

Channel *ChannelStore::getChannel(std::string name)
{
	std::map<std::string, Channel>::iterator chan = this->_channels.find(name);
	if (chan == this->_channels.end())
		return (NULL);
	return (&chan->second);
}

Channel &ChannelStore::getOrCreate(std::string name)
{
    std::pair<std::map<std::string, Channel>::iterator, bool> result = 
        this->_channels.insert(std::make_pair(name, Channel(name)));
    return result.first->second;
}

Channel &ChannelStore::addChannel(const std::string &name)
{
	this->_channels.insert(std::make_pair(name, Channel(name)));
	return (this->_channels.end()->second);
}

bool ChannelStore::delChannel(std::string name)
{
	return (this->_channels.erase(name));
}
